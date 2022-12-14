#include "macros.h"
#include <stddef.h>

namespace android {

template <class T, size_t SIZE>
class RingBuffer {
    PREVENT_COPY_AND_ASSIGN(RingBuffer);

public:
    RingBuffer() {}
    ~RingBuffer() {}

    constexpr size_t capacity() const { return SIZE; }
    size_t size() const { return mCount; }

    T& next() {
        mHead = (mHead + 1) % SIZE;
        if (mCount < SIZE) {
            mCount++;
        }
        return mBuffer[mHead];
    }

    T& front() { return (*this)[0]; }

    T& back() { return (*this)[size() - 1]; }

    T& operator[](size_t index) { return mBuffer[(mHead + index + 1) % mCount]; }

    const T& operator[](size_t index) const { return mBuffer[(mHead + index + 1) % mCount]; }

    void clear() {
        mCount = 0;
        mHead = -1;
    }

private:
    T mBuffer[SIZE];
    int mHead = -1;
    size_t mCount = 0;
};
} //namespace android
