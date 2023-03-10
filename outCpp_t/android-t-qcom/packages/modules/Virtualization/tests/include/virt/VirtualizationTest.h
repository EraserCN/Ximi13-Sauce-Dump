/*
 * Copyright (C) 2021 The Android Open Source Project
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

#include "android/system/virtualizationservice/IVirtualMachine.h"
#include "android/system/virtualizationservice/IVirtualizationService.h"
#include "binder/IServiceManager.h"
#include "gtest/gtest.h"

using namespace android;
using namespace android::system::virtualizationservice;

namespace virt {

class VirtualizationTest : public ::testing::Test {
protected:
    void SetUp() override;

    sp<IVirtualizationService> mVirtualizationService;
};

} // namespace virt
