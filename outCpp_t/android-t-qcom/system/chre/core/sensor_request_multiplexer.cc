/*
 * Copyright (C) 2019 The Android Open Source Project
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

#include "chre/core/sensor_request_multiplexer.h"

#include "chre/core/event_loop_manager.h"

namespace chre {

const SensorRequest *SensorRequestMultiplexer::findRequest(
    uint16_t instanceId, size_t *index) const {
  const DynamicVector<SensorRequest> &requests = getRequests();
  for (size_t i = 0; i < requests.size(); i++) {
    const SensorRequest &sensorRequest = requests[i];
    if (sensorRequest.getInstanceId() == instanceId) {
      if (index != nullptr) {
        *index = i;
      }
      return &sensorRequest;
    }
  }

  return nullptr;
}

}  // namespace chre