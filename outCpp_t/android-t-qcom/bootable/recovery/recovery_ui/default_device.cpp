/*
 * Copyright (C) 2009 The Android Open Source Project
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

#include "recovery_ui/device.h"
#include "recovery_ui/screen_ui.h"
// MIUI ADD: START
#include "recovery_ui/mi_screen_ui.h"

#ifdef MTK_VENDOR
#include <mt_recovery_ui.h>
#endif
// END

Device* make_device() {
  // MIUI MOD: START
  // 
  // return new Device(new ScreenRecoveryUI);
#ifdef MTK_VENDOR
  return new MTK_Device(new MiScreenRecoveryUI());
#else
  return new Device(new MiScreenRecoveryUI());
#endif
  // END
}
