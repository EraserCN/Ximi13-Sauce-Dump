/*
 * Copyright (C) 2020 The Android Open Source Project
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

#ifndef BUFFERINFOLIBDRM_H_
#define BUFFERINFOLIBDRM_H_

#include <hardware/gralloc.h>

#include "bufferinfo/BufferInfoGetter.h"

namespace android {

class BufferInfoLibdrm : public LegacyBufferInfoGetter {
 public:
  using LegacyBufferInfoGetter::LegacyBufferInfoGetter;
  int ConvertBoInfo(buffer_handle_t handle, hwc_drm_bo_t *bo) override;
  int ValidateGralloc() override;

 private:
  bool GetYuvPlaneInfo(int num_fds, buffer_handle_t handle, hwc_drm_bo_t *bo);
};

}  // namespace android

#endif
