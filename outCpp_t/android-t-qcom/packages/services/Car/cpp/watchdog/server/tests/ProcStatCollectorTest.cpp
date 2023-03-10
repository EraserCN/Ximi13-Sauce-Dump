/*
 * Copyright 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ProcStatCollector.h"

#include <android-base/file.h>
#include <android-base/stringprintf.h>
#include <gmock/gmock.h>

#include <inttypes.h>

#include <string>

namespace android {
namespace automotive {
namespace watchdog {

using ::android::base::StringPrintf;
using ::android::base::WriteStringToFile;

namespace {

std::string toString(const ProcStatInfo& info) {
    const auto& cpuStats = info.cpuStats;
    return StringPrintf("Cpu Stats:\nUserTime: %" PRIu64 " NiceTime: %" PRIu64 " SysTime: %" PRIu64
                        " IdleTime: %" PRIu64 " IoWaitTime: %" PRIu64 " IrqTime: %" PRIu64
                        " SoftIrqTime: %" PRIu64 " StealTime: %" PRIu64 " GuestTime: %" PRIu64
                        " GuestNiceTime: %" PRIu64 "\nNumber of running processes: %" PRIu32
                        "\nNumber of blocked processes: %" PRIu32,
                        cpuStats.userTime, cpuStats.niceTime, cpuStats.sysTime, cpuStats.idleTime,
                        cpuStats.ioWaitTime, cpuStats.irqTime, cpuStats.softIrqTime,
                        cpuStats.stealTime, cpuStats.guestTime, cpuStats.guestNiceTime,
                        info.runnableProcessCount, info.ioBlockedProcessCount);
}

}  // namespace

TEST(ProcStatCollectorTest, TestValidStatFile) {
    constexpr char firstSnapshot[] =
            "cpu  6200 5700 1700 3100 1100 5200 3900 0 0 0\n"
            "cpu0 2400 2900 600 690 340 4300 2100 0 0 0\n"
            "cpu1 1900 2380 510 760 51 370 1500 0 0 0\n"
            "cpu2 900 400 400 1000 600 400 160 0 0 0\n"
            "cpu3 1000 20 190 650 109 130 140 0 0 0\n"
            "intr 694351583 0 0 0 297062868 0 5922464 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
            "0 0\n"
            /* Skipped most of the intr line as it is not important for testing the ProcStat parsing
             * logic.
             */
            "ctxt 579020168\n"
            "btime 1579718450\n"
            "processes 113804\n"
            "procs_running 17\n"
            "procs_blocked 5\n"
            "softirq 33275060 934664 11958403 5111 516325 200333 0 341482 10651335 0 8667407\n";
    ProcStatInfo expectedFirstDelta;
    expectedFirstDelta.cpuStats = {
            .userTime = 6200,
            .niceTime = 5700,
            .sysTime = 1700,
            .idleTime = 3100,
            .ioWaitTime = 1100,
            .irqTime = 5200,
            .softIrqTime = 3900,
            .stealTime = 0,
            .guestTime = 0,
            .guestNiceTime = 0,
    };
    expectedFirstDelta.runnableProcessCount = 17;
    expectedFirstDelta.ioBlockedProcessCount = 5;

    TemporaryFile tf;
    ASSERT_NE(tf.fd, -1);
    ASSERT_TRUE(WriteStringToFile(firstSnapshot, tf.path));

    ProcStatCollector collector(tf.path);
    collector.init();

    ASSERT_TRUE(collector.enabled()) << "Temporary file is inaccessible";
    ASSERT_RESULT_OK(collector.collect());

    const auto& actualFirstDelta = collector.deltaStats();
    EXPECT_EQ(expectedFirstDelta, actualFirstDelta) << "First snapshot doesn't match.\nExpected:\n"
                                                    << toString(expectedFirstDelta) << "\nActual:\n"
                                                    << toString(actualFirstDelta);

    constexpr char secondSnapshot[] =
            "cpu  16200 8700 2000 4100 2200 6200 5900 0 0 0\n"
            "cpu0 4400 3400 700 890 800 4500 3100 0 0 0\n"
            "cpu1 5900 3380 610 960 100 670 2000 0 0 0\n"
            "cpu2 2900 1000 450 1400 800 600 460 0 0 0\n"
            "cpu3 3000 920 240 850 500 430 340 0 0 0\n"
            "intr 694351583 0 0 0 297062868 0 5922464 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
            "0 0\n"
            "ctxt 579020168\n"
            "btime 1579718450\n"
            "processes 113804\n"
            "procs_running 10\n"
            "procs_blocked 2\n"
            "softirq 33275060 934664 11958403 5111 516325 200333 0 341482 10651335 0 8667407\n";
    ProcStatInfo expectedSecondDelta;
    expectedSecondDelta.cpuStats = {
            .userTime = 10000,
            .niceTime = 3000,
            .sysTime = 300,
            .idleTime = 1000,
            .ioWaitTime = 1100,
            .irqTime = 1000,
            .softIrqTime = 2000,
            .stealTime = 0,
            .guestTime = 0,
            .guestNiceTime = 0,
    };
    expectedSecondDelta.runnableProcessCount = 10;
    expectedSecondDelta.ioBlockedProcessCount = 2;

    ASSERT_TRUE(WriteStringToFile(secondSnapshot, tf.path));
    ASSERT_RESULT_OK(collector.collect());

    const auto& actualSecondDelta = collector.deltaStats();
    EXPECT_EQ(expectedSecondDelta, actualSecondDelta)
            << "Second snapshot doesnt't match.\nExpected:\n"
            << toString(expectedSecondDelta) << "\nActual:\n"
            << toString(actualSecondDelta);
}

TEST(ProcStatCollectorTest, TestErrorOnCorruptedStatFile) {
    constexpr char contents[] =
            "cpu  6200 5700 1700 3100 CORRUPTED DATA\n"
            "cpu0 2400 2900 600 690 340 4300 2100 0 0 0\n"
            "cpu1 1900 2380 510 760 51 370 1500 0 0 0\n"
            "cpu2 900 400 400 1000 600 400 160 0 0 0\n"
            "cpu3 1000 20 190 650 109 130 140 0 0 0\n"
            "intr 694351583 0 0 0 297062868 0 5922464 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
            "0 0\n"
            "ctxt 579020168\n"
            "btime 1579718450\n"
            "processes 113804\n"
            "procs_running 17\n"
            "procs_blocked 5\n"
            "softirq 33275060 934664 11958403 5111 516325 200333 0 341482 10651335 0 8667407\n";
    TemporaryFile tf;
    ASSERT_NE(tf.fd, -1);
    ASSERT_TRUE(WriteStringToFile(contents, tf.path));

    ProcStatCollector collector(tf.path);
    collector.init();

    ASSERT_TRUE(collector.enabled()) << "Temporary file is inaccessible";
    EXPECT_FALSE(collector.collect().ok()) << "No error returned for corrupted file";
}

TEST(ProcStatCollectorTest, TestErrorOnMissingCpuLine) {
    constexpr char contents[] =
            "cpu0 2400 2900 600 690 340 4300 2100 0 0 0\n"
            "cpu1 1900 2380 510 760 51 370 1500 0 0 0\n"
            "cpu2 900 400 400 1000 600 400 160 0 0 0\n"
            "cpu3 1000 20 190 650 109 130 140 0 0 0\n"
            "intr 694351583 0 0 0 297062868 0 5922464 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
            "0 0\n"
            "ctxt 579020168\n"
            "btime 1579718450\n"
            "processes 113804\n"
            "procs_running 17\n"
            "procs_blocked 5\n"
            "softirq 33275060 934664 11958403 5111 516325 200333 0 341482 10651335 0 8667407\n";
    TemporaryFile tf;
    ASSERT_NE(tf.fd, -1);
    ASSERT_TRUE(WriteStringToFile(contents, tf.path));

    ProcStatCollector collector(tf.path);
    collector.init();

    ASSERT_TRUE(collector.enabled()) << "Temporary file is inaccessible";
    EXPECT_FALSE(collector.collect().ok()) << "No error returned due to missing cpu line";
}

TEST(ProcStatCollectorTest, TestErrorOnMissingProcsRunningLine) {
    constexpr char contents[] =
            "cpu  16200 8700 2000 4100 1250 6200 5900 0 0 0\n"
            "cpu0 2400 2900 600 690 340 4300 2100 0 0 0\n"
            "cpu1 1900 2380 510 760 51 370 1500 0 0 0\n"
            "cpu2 900 400 400 1000 600 400 160 0 0 0\n"
            "cpu3 1000 20 190 650 109 130 140 0 0 0\n"
            "intr 694351583 0 0 0 297062868 0 5922464 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
            "0 0\n"
            "ctxt 579020168\n"
            "btime 1579718450\n"
            "processes 113804\n"
            "procs_blocked 5\n"
            "softirq 33275060 934664 11958403 5111 516325 200333 0 341482 10651335 0 8667407\n";
    TemporaryFile tf;
    ASSERT_NE(tf.fd, -1);
    ASSERT_TRUE(WriteStringToFile(contents, tf.path));

    ProcStatCollector collector(tf.path);
    collector.init();

    ASSERT_TRUE(collector.enabled()) << "Temporary file is inaccessible";
    EXPECT_FALSE(collector.collect().ok()) << "No error returned due to missing procs_running line";
}

TEST(ProcStatCollectorTest, TestErrorOnMissingProcsBlockedLine) {
    constexpr char contents[] =
            "cpu  16200 8700 2000 4100 1250 6200 5900 0 0 0\n"
            "cpu0 2400 2900 600 690 340 4300 2100 0 0 0\n"
            "cpu1 1900 2380 510 760 51 370 1500 0 0 0\n"
            "cpu2 900 400 400 1000 600 400 160 0 0 0\n"
            "cpu3 1000 20 190 650 109 130 140 0 0 0\n"
            "intr 694351583 0 0 0 297062868 0 5922464 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
            "0 0\n"
            "ctxt 579020168\n"
            "btime 1579718450\n"
            "processes 113804\n"
            "procs_running 17\n"
            "softirq 33275060 934664 11958403 5111 516325 200333 0 341482 10651335 0 8667407\n";
    TemporaryFile tf;
    ASSERT_NE(tf.fd, -1);
    ASSERT_TRUE(WriteStringToFile(contents, tf.path));

    ProcStatCollector collector(tf.path);
    collector.init();

    ASSERT_TRUE(collector.enabled()) << "Temporary file is inaccessible";
    EXPECT_FALSE(collector.collect().ok()) << "No error returned due to missing procs_blocked line";
}

TEST(ProcStatCollectorTest, TestErrorOnUnknownProcsLine) {
    constexpr char contents[] =
            "cpu  16200 8700 2000 4100 1250 6200 5900 0 0 0\n"
            "cpu0 2400 2900 600 690 340 4300 2100 0 0 0\n"
            "cpu1 1900 2380 510 760 51 370 1500 0 0 0\n"
            "cpu2 900 400 400 1000 600 400 160 0 0 0\n"
            "cpu3 1000 20 190 650 109 130 140 0 0 0\n"
            "intr 694351583 0 0 0 297062868 0 5922464 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
            "0 0\n"
            "ctxt 579020168\n"
            "btime 1579718450\n"
            "processes 113804\n"
            "procs_running 17\n"
            "procs_blocked 5\n"
            "procs_sleeping 15\n"
            "softirq 33275060 934664 11958403 5111 516325 200333 0 341482 10651335 0 8667407\n";
    TemporaryFile tf;
    ASSERT_NE(tf.fd, -1);
    ASSERT_TRUE(WriteStringToFile(contents, tf.path));

    ProcStatCollector collector(tf.path);
    collector.init();

    ASSERT_TRUE(collector.enabled()) << "Temporary file is inaccessible";
    EXPECT_FALSE(collector.collect().ok()) << "No error returned due to unknown procs line";
}

TEST(ProcStatCollectorTest, TestProcStatContentsFromDevice) {
    ProcStatCollector collector;
    collector.init();

    ASSERT_TRUE(collector.enabled()) << kProcStatPath << " file is inaccessible";
    ASSERT_RESULT_OK(collector.collect());

    const auto& info = collector.deltaStats();
    /* The below checks should pass because the /proc/stats file should have the CPU time spent
     * since bootup and there should be at least one running process.
     */
    EXPECT_GT(info.totalCpuTime(), static_cast<uint64_t>(0));
    EXPECT_GT(info.totalProcessCount(), static_cast<uint32_t>(0));
}

}  // namespace watchdog
}  // namespace automotive
}  // namespace android
