// Copyright (C) 2017 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <functional>
#include <future>
#include <optional>
#include <utility>
#include <vector>

#include "base/Compiler.h"
#include "base/ConditionVariable.h"
#include "base/FunctorThread.h"
#include "base/Lock.h"

//
// WorkerThread<Item> encapsulates an asynchronous processing queue for objects
// of type Item. It manages queue memory, runs processing function in a separate
// thread and allows the processing function to stop it at any moment.
//
// Expected usage of the class:
//
// - Define an object to store all data for processing:
//      struct WorkItem { int number; };
//
// - Create a WorkerThread with processing function:
//      WorkerThread<WorkItem> worker([](WorkItem&& item) {
//          std::cout << item.number;
//          return item.number
//              ? WorkerProcessingResult::Continue
//              : WorkerProcessingResult::Stop;
//      });
//
// - Start the worker and send some data for asynchronous processing
//      worker.start();
//      worker.enqueue({1});
//      worker.enqueue({2});
//      worker.enqueue({});     // <--- this item will stop processing.
//      worker.join();
//
// WorkerThread<>'s all methods are thread-safe, with an expectation that the
// work could be added from any number of threads at once.
//
// Note: destructor calls join() implicitly - it's better to send some
// end-of-work marker before trying to destroy a worker thread.
//

namespace android {
namespace base {

// Return values for a worker thread's processing function.
enum class WorkerProcessingResult { Continue, Stop };

template <class Item>
class WorkerThread {
    DISALLOW_COPY_AND_ASSIGN(WorkerThread);

public:
    using Result = WorkerProcessingResult;
    // A function that's called for each enqueued item in a separate thread.
    using Processor = std::function<Result(Item&&)>;

    WorkerThread(Processor&& processor)
        : mProcessor(std::move(processor)), mThread([this]() { worker(); }) {
        mQueue.reserve(10);
    }
    ~WorkerThread() { join(); }

    // Starts the worker thread.
    bool start() {
        mStarted = true;
        if (!mThread.start()) {
            mFinished = true;
            return false;
        }
        return true;
    }
    bool isStarted() const { return mStarted; }
    // Waits for all enqueue()'d items to finish.
    void waitQueuedItems() {
        if (!mStarted || mFinished)
            return;

        // Enqueue an empty sync command.
        std::future<void> completeFuture = enqueueImpl(Command());
        completeFuture.wait();
    }
    // Waits for worker thread to complete.
    void join() { mThread.wait(); }

    // Moves the |item| into internal queue for processing.
    std::future<void> enqueue(Item&& item) {
        return enqueueImpl(Command(std::move(item)));
    }

   private:
    struct Command {
        Command() : mWorkItem(std::nullopt) {}
        Command(Item&& it) : mWorkItem(std::move(it)) {}
        Command(Command&& other)
            : mCompletedPromise(std::move(other.mCompletedPromise)),
              mWorkItem(std::move(other.mWorkItem)) {}

        std::promise<void> mCompletedPromise;
        std::optional<Item> mWorkItem;
    };

    std::future<void> enqueueImpl(Command command) {
        base::AutoLock lock(mLock);
        bool signal = mQueue.empty();
        std::future<void> res = command.mCompletedPromise.get_future();
        mQueue.emplace_back(std::move(command));
        if (signal) {
            mCv.signalAndUnlock(&lock);
        }
        return res;
    }

    void worker() {
        std::vector<Command> todo;
        todo.reserve(10);
        for (;;) {
            {
                base::AutoLock lock(mLock);
                while (mQueue.empty()) {
                    mCv.wait(&lock);
                }
                todo.swap(mQueue);
            }

            for (Command& item : todo) {
                bool shouldStop = false;
                if (item.mWorkItem) {
                    // Normal work item
                    if (mProcessor(std::move(item.mWorkItem.value())) ==
                        Result::Stop) {
                        shouldStop = true;
                    }
                }
                item.mCompletedPromise.set_value();
                if (shouldStop) {
                    return;
                }
            }

            todo.clear();
        }
        mFinished = true;
    }

    Processor mProcessor;
    base::FunctorThread mThread;
    std::vector<Command> mQueue;
    base::Lock mLock;
    base::ConditionVariable mCv;

    bool mStarted = false;
    bool mFinished = false;
};

}  // namespace base
}  // namespace android
