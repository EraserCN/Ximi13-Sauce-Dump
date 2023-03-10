/*
 * Copyright (C) 2018 The Android Open Source Project
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
#pragma once

#include <sys/types.h>

#include <cstdint>

#include "Layer.h"

namespace android {

class ContainerLayer : public Layer {
public:
    explicit ContainerLayer(const LayerCreationArgs&);
    ~ContainerLayer() override;

    const char* getType() const override { return "ContainerLayer"; }
    bool isVisible() const override;

    bool isCreatedFromMainThread() const override { return true; }

protected:
    bool canDrawShadows() const override { return false; }
#ifdef MI_SF_FEATURE
    bool canDrawHdrDim() const override { return false; }
#endif
    sp<Layer> createClone() override;
};

} // namespace android
