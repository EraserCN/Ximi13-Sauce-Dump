/*
 * Copyright 2017 The Android Open Source Project
 *  Copyright 2018-2020 NXP
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

#include <string>
#include <vector>

#include <config.h>

#define NAME_UWB_BOARD_VARIANT_CONFIG "UWB_BOARD_VARIANT_CONFIG"
#define NAME_UWB_BOARD_VARIANT_VERSION "UWB_BOARD_VARIANT_VERSION"
#define NAME_UWB_DEBUG_DEFAULT_CONFIG "UWB_DEBUG_DEFAULT_CONFIG"
#define NAME_UWB_CORE_DEVICE_DEFAULT_CONFIG "UWB_CORE_DEVICE_DEFAULT_CONFIG"
#define NAME_UWB_LOW_POWER_MODE "UWB_LOW_POWER_MODE"
#define NAME_UWB_DPD_ENTRY_TIMEOUT "UWB_DPD_ENTRY_TIMEOUT"

/* Configs from vendor interface */
#define NAME_UWB_CORE_EXT_DEVICE_DEFAULT_CONFIG "UWB_CORE_EXT_DEVICE_DEFAULT_CONFIG"
#define NAME_ANTENNA_PAIR_SELECTION_CONFIG1 "ANTENNA_PAIR_SELECTION_CONFIG1"
#define NAME_ANTENNA_PAIR_SELECTION_CONFIG2 "ANTENNA_PAIR_SELECTION_CONFIG2"
#define NAME_ANTENNA_PAIR_SELECTION_CONFIG3 "ANTENNA_PAIR_SELECTION_CONFIG3"
#define NAME_ANTENNA_PAIR_SELECTION_CONFIG4 "ANTENNA_PAIR_SELECTION_CONFIG4"
#define NAME_ANTENNA_PAIR_SELECTION_CONFIG5 "ANTENNA_PAIR_SELECTION_CONFIG5"
#define NAME_NXP_UWB_XTAL_38MHZ_CONFIG "NXP_UWB_XTAL_38MHZ_CONFIG"
#define NAME_NXP_CORE_CONF_BLK "NXP_CORE_CONF_BLK_"

#define CHECK_RETURN(condition, str, ret) \
    do { \
        if (condition) { \
            return ret; \
        } \
    } while (0)
#define CHECK_RETURN_VOID(condition, str) \
    do { \
        if (condition) { \
            return; \
        } \
    } while (0)
class UwbConfig {
 public:
  static bool hasKey(const std::string& key);
  static std::string getString(const std::string& key);
  static std::string getString(const std::string& key,
                               std::string default_value);
  static unsigned getUnsigned(const std::string& key);
  static unsigned getUnsigned(const std::string& key, unsigned default_value);
  static std::vector<uint8_t> getBytes(const std::string& key);
  static void clear();
 private:
  void loadConfig();
  static UwbConfig& getInstance();
  UwbConfig();

  ConfigFile config_;
};
