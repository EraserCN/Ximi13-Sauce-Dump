/*
 *  Copyright (C) 2013 ST Microelectronics S.A.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  Provide extensions for the ST implementation of the NFC stack
 */
#include <android-base/stringprintf.h>
#include <base/logging.h>
#include <nativehelper/ScopedLocalRef.h>
#include <nativehelper/ScopedPrimitiveArray.h>

#include <dlfcn.h>
#include "NfcStExtensions.h"
#include "StNfcJni.h"
#include "StRawJni.h"

#include "StCardEmulationEmbedded.h"

using android::base::StringPrintf;
extern bool nfc_debug_enabled;

#define IS_64BIT (sizeof(void *) == 8)
namespace android {
const char *JNIVersion = "JNI version 00.12.16.10";

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_getFirmwareVersion
**
** Description:     Connect to the secure element.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static jbyteArray nativeNfcStExtensions_getFirmwareVersion(JNIEnv *e, jobject) {
  uint8_t version_sw[NfcStExtensions::getInstance().FW_VERSION_SIZE];
  memset(version_sw, 0, sizeof version_sw);
  NfcStExtensions::getInstance().getFirmwareVersion(version_sw);
  jbyteArray result;

  {
    // copy results back to java
    result = e->NewByteArray(NfcStExtensions::getInstance().FW_VERSION_SIZE);
    if (result != NULL) {
      e->SetByteArrayRegion(result, 0,
                            NfcStExtensions::getInstance().FW_VERSION_SIZE,
                            (jbyte *)version_sw);
    }
  }

  return result;
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_getHWVersion
**
** Description:     Connect to the secure element.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static jbyteArray nativeNfcStExtensions_getHWVersion(JNIEnv *e, jobject) {
  jbyteArray result = NULL;
  uint8_t version_hw[NfcStExtensions::getInstance().HW_VERSION_SIZE];
  memset(version_hw, 0, sizeof version_hw);

  NfcStExtensions::getInstance().getHWVersion(version_hw);

  {
    // copy results back to java
    result = e->NewByteArray(NfcStExtensions::getInstance().HW_VERSION_SIZE);
    if (result != NULL) {
      e->SetByteArrayRegion(result, 0,
                            NfcStExtensions::getInstance().HW_VERSION_SIZE,
                            (jbyte *)version_hw);
    }
  }

  return result;
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_getCRCConfiguration
**
** Description:     Connect to the secure element.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static jbyteArray nativeNfcStExtensions_getCRCConfiguration(JNIEnv *e,
                                                            jobject) {
  jbyteArray result = NULL;
  uint8_t crc_config[NfcStExtensions::getInstance().CRC_CONFIG_SIZE];
  memset(crc_config, 0, sizeof crc_config);
  NfcStExtensions::getInstance().getCRCConfiguration(crc_config);

  {
    // copy results back to java
    result = e->NewByteArray(NfcStExtensions::getInstance().CRC_CONFIG_SIZE);
    if (result != NULL) {
      e->SetByteArrayRegion(result, 0,
                            NfcStExtensions::getInstance().CRC_CONFIG_SIZE,
                            (jbyte *)crc_config);
    }
  }

  return result;
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_getCustomerData
**
** Description:     Connect to the secure element.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static jbyteArray nativeNfcStExtensions_getCustomerData(JNIEnv *e, jobject) {
  uint8_t customerData[8];
  memset(customerData, 0, sizeof(customerData));
  int ret;
  jbyteArray result;

  ret = NfcStExtensions::getInstance().getCustomerData(customerData);

  {
    // copy results back to java
    result = e->NewByteArray(sizeof(customerData));
    if (result != NULL) {
      e->SetByteArrayRegion(result, 0, sizeof(customerData),
                            (jbyte *)customerData);
    }
  }

  return result;
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_getSWVersion
**
** Description:     Connect to the secure element.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static jbyteArray nativeNfcStExtensions_getSWVersion(JNIEnv *e, jobject) {
  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf("%s; enter;", __func__);
  jbyteArray result = NULL;
  void *handle = 0;
  int len = 0, res_len = 0;
  const char *separator = "+";
  char lib_path[PATH_MAX];
  if (IS_64BIT) {
    strlcpy(lib_path, "/system_ext/lib64/", sizeof(lib_path));
  } else {
    strlcpy(lib_path, "/system_ext/lib/", sizeof(lib_path));
  }

  char **temp;

  // Get Core stack version - idx 1
  strlcat(lib_path, "libstnfc-nci.so", sizeof(lib_path));
  handle = dlopen(lib_path, RTLD_LAZY);
  if (!handle) {
    LOG(ERROR) << StringPrintf("%s; failed to load the library", __func__);
    return NULL;
  }
  temp = (char **)dlsym(handle, "coreStackVersion");

  if (temp == nullptr) {
    LOG(ERROR) << StringPrintf("%s; failed to find coreStackVersion", __func__);
    return result;
  }

  len = strlen(*temp);
  char *core_stack_version = (char *)malloc(len + 1);

  if (core_stack_version == nullptr) {
    LOG(ERROR) << StringPrintf("%s; coreStackVersion is null", __func__);
    return result;
  }

  memcpy(core_stack_version, *temp, (len + 1));
  dlclose(handle);
  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
      "%s; Core stack version is %s", __func__, core_stack_version);
  res_len += len;

  // Get NfcService/JNI version -idx 2 => JNIVersion in this file
  len = strlen(JNIVersion);
  DLOG_IF(INFO, nfc_debug_enabled)
      << StringPrintf("%s; JNI version is %s;", __func__, JNIVersion);
  res_len += len;

  // Android version - idx 3

  handle = dlopen(lib_path, RTLD_LAZY);
  if (!handle) {
    LOG(ERROR) << StringPrintf("%s; failed to load the library", __func__);
    free(core_stack_version);
    dlclose(handle);
    return NULL;
  }
  temp = (char **)dlsym(handle, "androidVersion");

  if (temp == nullptr) {
    LOG(ERROR) << StringPrintf("%s; failed to find androidVersion", __func__);
    free(core_stack_version);
    dlclose(handle);
    return result;
  }

  len = strlen(*temp);
  char *android_version = (char *)malloc(len + 1);

  if (android_version == nullptr) {
    LOG(ERROR) << StringPrintf("%s; android_version is null", __func__);
    free(core_stack_version);
    free(android_version);
    dlclose(handle);
    return result;
  }

  memcpy(android_version, *temp, (len + 1));
  dlclose(handle);
  DLOG_IF(INFO, nfc_debug_enabled)
      << StringPrintf("%s; Android version is %s", __func__, android_version);
  res_len += len;

  // Framework version is handled in framework -idx 4

  // copy results back to java
  char *sw_version = (char *)malloc(res_len + 3 + 1);  // 3 separators, final \0
  if (sw_version && core_stack_version && android_version) {
    strlcat(sw_version, core_stack_version, sizeof(sw_version));
    strlcat(sw_version, separator, sizeof(sw_version));
    strlcat(sw_version, JNIVersion, sizeof(sw_version));
    strlcat(sw_version, separator, sizeof(sw_version));
    strlcat(sw_version, android_version, sizeof(sw_version));

    result = e->NewByteArray(res_len + 3 + 1);
    if (result != NULL) {
      e->SetByteArrayRegion(result, 0, (res_len + 3 + 1), (jbyte *)sw_version);
    }
  }

  free(sw_version);
  free(core_stack_version);
  free(android_version);

  return result;
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_isUiccConnected
**
** Description:     Check if the UICC is connected.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static jboolean nativeNfcStExtensions_isUiccConnected(JNIEnv *e, jobject) {
  return NfcStExtensions::getInstance().isSEConnected(0x02);
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_iseSEConnected
**
** Description:     Check if the eSE is connected.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static jboolean nativeNfcStExtensions_iseSEConnected(JNIEnv *e, jobject) {
  return NfcStExtensions::getInstance().isSEConnected(0xC0);
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_isSEConnected
**
** Description:     Check if the given host HostID is connected.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static jboolean nativeNfcStExtensions_isSEConnected(JNIEnv *e, jobject,
                                                    jint HostID) {
  jboolean result = NfcStExtensions::getInstance().isSEConnected(HostID);
  return result;
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_startLoopback
**
** Description:     Connect to the secure element.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static jint nativeNfcStExtensions_loopback(JNIEnv *e, jobject) {
  jint ret = NfcStExtensions::getInstance().handleLoopback();
  return ret;
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_getHceUserProp
**
** Description:     Connect to the secure element.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static jint nativeNfcStExtensions_getHceUserProp(JNIEnv *e, jobject) {
  uint32_t res = NfcStExtensions::getInstance().getHceUserProp();
  return res;
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_setRfConfiguration
**
** Description:     Connect to the secure element.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static void nativeNfcStExtensions_setRfConfiguration(JNIEnv *e, jobject,
                                                     jint modeBitmap,
                                                     jbyteArray techArray) {
  ScopedByteArrayRW bytes(e, techArray);
  NfcStExtensions::getInstance().setRfConfiguration(
      modeBitmap, reinterpret_cast<uint8_t *>(&bytes[0]));
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_getRfConfiguration
**
** Description:     Connect to the secure element.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static int nativeNfcStExtensions_getRfConfiguration(JNIEnv *e, jobject,
                                                    jbyteArray techArray) {
  uint8_t outputArray[NfcStExtensions::getInstance().RF_CONFIG_ARRAY_SIZE];
  int modeBitmap;

  modeBitmap = NfcStExtensions::getInstance().getRfConfiguration(outputArray);

  e->SetByteArrayRegion(techArray, 0,
                        NfcStExtensions::getInstance().RF_CONFIG_ARRAY_SIZE,
                        (jbyte *)outputArray);

  return modeBitmap;
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_setRfBitmap
**
** Description:     Connect to the secure element.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:
**
*******************************************************************************/
static void nativeNfcStExtensions_setRfBitmap(JNIEnv *e, jobject,
                                              jint modeBitmap) {
  NfcStExtensions::getInstance().setRfBitmap(modeBitmap);
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_updatePipesInfo
**
** Description:     Send data to the secure element; retrieve response.
**                  e: JVM environment.
**                  o: Java object.
**                  handle: Secure element's handle.
**                  data: Data to send.
**
** Returns:         Buffer of received data.
**
*******************************************************************************/
static jint nativeNfcStExtensions_updatePipesInfo(JNIEnv *e, jobject o) {
  int pipe_id;
  jint host_id;

  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf("%s; enter;", __func__);

  bool res = NfcStExtensions::getInstance().getPipesInfo();
  if (res == true) {
    pipe_id = NfcStExtensions::getInstance().getPipeIdForGate(
        NfcStExtensions::getInstance().DH_HCI_ID, 0x41);

    if (pipe_id != 0xFF) {
      host_id = NfcStExtensions::getInstance().getHostIdForPipe(pipe_id);
      if (host_id != 0xFF) {
        DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf("%s; exit:", __func__);
        return host_id;
      }
    }
  }

  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf("%s; exit:", __func__);
  return 0xFF;
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_setDefaultOffHostRoute
**
** Description:     Get the technology / protocol routing table.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static void nativeNfcStExtensions_setDefaultOffHostRoute(JNIEnv *e, jobject,
                                                         jint route) {
  NfcStExtensions::getInstance().setDefaultOffHostRoute(route);
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_getDefaultOffHostRoute
**
** Description:     Get the technology / protocol routing table.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static jint nativeNfcStExtensions_getDefaultOffHostRoute(JNIEnv *e, jobject) {
  return NfcStExtensions::getInstance().getDefaultOffHostRoute();
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_getProprietaryConfigSettings
**
** Description:     Get the Proprietary Config Settings.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static jboolean nativeNfcStExtensions_getProprietaryConfigSettings(
    JNIEnv *e, jobject, jint SubSetId, jint byteNb, jint bitNb) {
  return NfcStExtensions::getInstance().getProprietaryConfigSettings(
      SubSetId, byteNb, bitNb);
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_setProprietaryConfigSettings
**
** Description:     Set the Proprietary Config Settings.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static void nativeNfcStExtensions_setProprietaryConfigSettings(
    JNIEnv *e, jobject, jint SubSetId, jint byteNb, jint bitNb,
    jboolean status) {
  NfcStExtensions::getInstance().setProprietaryConfigSettings(SubSetId, byteNb,
                                                              bitNb, status);
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_getPipesList
**
** Description:     Get the list and status of pipes for a given host.
**                  e: JVM environment.
**                  o: Java object.
**                  host_id: Host to investigate
**
** Returns:         Java object containing Pipes information
**
*******************************************************************************/
static jint nativeNfcStExtensions_getPipesList(JNIEnv *e, jobject, jint host_id,
                                               jbyteArray list) {
  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf("%s; enter;", __func__);
  int i, nb_pipes = 0, host_idx;

  NfcStExtensions::getInstance().getPipesInfo();

  if (host_id == 1) {
    host_idx = NfcStExtensions::getInstance().DH_IDX;
  } else if (host_id == 2) {
    host_idx = NfcStExtensions::getInstance().UICC_IDX;
  } else if (host_id == 192) {
    host_idx = NfcStExtensions::getInstance().ESE_IDX;
  } else {
    return 0xff;
  }

  nb_pipes = NfcStExtensions::getInstance().mPipesInfo[host_idx].nb_pipes;

  DLOG_IF(INFO, nfc_debug_enabled)
      << StringPrintf("%s; nb_pipes: %d", __func__, nb_pipes);

  uint8_t listArray[nb_pipes];

  for (i = 0; i < nb_pipes; i++) {
    listArray[i] =
        NfcStExtensions::getInstance().mPipesInfo[host_idx].data[i].pipe_id;
    DLOG_IF(INFO, nfc_debug_enabled)
        << StringPrintf("%s; listArray[%d]= 0x%x", __func__, i, listArray[i]);
  }

  e->SetByteArrayRegion(list, 0, nb_pipes, (jbyte *)listArray);

  return nb_pipes;
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_getPipeInfo
**
** Description:     Get the list and status of pipes for a given host.
**                  e: JVM environment.
**                  o: Java object.
**                  host_id: Host to investigate
**
** Returns:         Java object containing Pipes information
**
*******************************************************************************/
static void nativeNfcStExtensions_getPipeInfo(JNIEnv *e, jobject, jint host_id,
                                              jint pipe_id, jbyteArray info) {
  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf("%s; enter;", __func__);
  int i, nb_pipes = 0, host_idx;

  if (host_id == 1) {
    host_idx = NfcStExtensions::getInstance().DH_IDX;
  } else if (host_id == 2) {
    host_idx = NfcStExtensions::getInstance().UICC_IDX;
  } else if (host_id == 192) {
    host_idx = NfcStExtensions::getInstance().ESE_IDX;
  } else {
    return;
  }
  nb_pipes = NfcStExtensions::getInstance().mPipesInfo[host_idx].nb_pipes;

  if (nb_pipes == 0xFF) {
    DLOG_IF(INFO, nfc_debug_enabled)
        << StringPrintf("%s; getPipesInfo() was not called!!;", __func__);
    return;
  }

  uint8_t infoArray[4] = {0xFF, 0xFF, 0xFF, 0xFF};

  if (nb_pipes > 15) {
    LOG(ERROR) << StringPrintf("%s; Nb of pipes >= 15", __func__);
    return;
  }

  for (i = 0; i < nb_pipes; i++) {
    if (NfcStExtensions::getInstance().mPipesInfo[host_idx].data[i].pipe_id ==
        pipe_id) {
      infoArray[0] = NfcStExtensions::getInstance()
                         .mPipesInfo[host_idx]
                         .data[i]
                         .pipe_state;
      infoArray[1] = NfcStExtensions::getInstance()
                         .mPipesInfo[host_idx]
                         .data[i]
                         .source_host;
      infoArray[2] = NfcStExtensions::getInstance()
                         .mPipesInfo[host_idx]
                         .data[i]
                         .source_gate;
      infoArray[3] =
          NfcStExtensions::getInstance().mPipesInfo[host_idx].data[i].dest_host;
      break;
    }
  }

  e->SetByteArrayRegion(info, 0, 4, (jbyte *)infoArray);
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_getAtr
**
** Description:     Get the list and status of pipes for a given host.
**                  e: JVM environment.
**                  o: Java object.
**                  host_id: Host to investigate
**
** Returns:         Java object containing Pipes information
**
*******************************************************************************/
static jbyteArray nativeNfcStExtensions_getAtr(JNIEnv *e, jobject) {
  int length;
  uint8_t data[30];
  jbyteArray atr = NULL;

  length = NfcStExtensions::getInstance().getATR(data);

  atr = e->NewByteArray(length);
  e->SetByteArrayRegion(atr, 0, length, (jbyte *)data);
  return atr;
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_EnableSE
**
** Description:     Connect/disconnect the secure element.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static jboolean nativeNfcStExtensions_EnableSE(JNIEnv *e, jobject, jint se_id,
                                               jboolean enable) {
  return NfcStExtensions::getInstance().EnableSE(se_id, enable);
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_connectEE
**
** Description:     Connect/disconnect the secure element.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static jboolean nativeNfcStExtensions_connectEE(JNIEnv *e, jobject,
                                                jint cee_id) {
  return StCardEmulationEmbedded::getInstance().connect(cee_id);
}

/*********************************************************************************
** Function:        nativeNfcStExtensions_transceiveEE
**
** Description:     Get the list and status of pipes for a given host.
**                  e: JVM environment.
**                  o: Java object.
**                  host_id: Host to investigate
**
** Returns:         Java object containing Pipes information
**
*******************************************************************************/
static jbyteArray nativeNfcStExtensions_transceiveEE(JNIEnv *e, jobject,
                                                     jint cee_id,
                                                     jbyteArray data_cmd) {
  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf("%s; enter;", __func__);

  uint8_t recvBuffer[1024];
  uint16_t recvBufferActualSize = 0;
  ScopedByteArrayRW bytes(e, data_cmd);
  bool rslt = false;

  rslt = StCardEmulationEmbedded::getInstance().transceive(
      cee_id, bytes.size(), reinterpret_cast<uint8_t *>(&bytes[0]),
      recvBufferActualSize, recvBuffer);

  jbyteArray result = e->NewByteArray(recvBufferActualSize);
  if (result != NULL) {
    e->SetByteArrayRegion(result, 0, recvBufferActualSize, (jbyte *)recvBuffer);
  }

  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
      "%s; exit: received data length =%d", __func__, recvBufferActualSize);
  return result;
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_disconnectEE
**
** Description:     Connect/disconnect the secure element.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static jboolean nativeNfcStExtensions_disconnectEE(JNIEnv *e, jobject,
                                                   jint cee_id) {
  return StCardEmulationEmbedded::getInstance().disconnect(cee_id);
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_connectGate
**
** Description:     Connect/disconnect the secure element.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static jint nativeNfcStExtensions_connectGate(JNIEnv *e, jobject, jint host_id,
                                              jint gate_id) {
  jint result = NfcStExtensions::getInstance().connectGate(host_id, gate_id);
  return result;
}

/*********************************************************************************
** Function:        nativeNfcStExtensions_transceive
**
** Description:     Get the list and status of pipes for a given host.
**                  e: JVM environment.
**                  o: Java object.
**                  host_id: Host to investigate
**
** Returns:         Java object containing Pipes information
**
*******************************************************************************/
static jbyteArray nativeNfcStExtensions_transceive(JNIEnv *e, jobject,
                                                   jint pipe_id, jint hciCmd,
                                                   jbyteArray data_cmd) {
  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf("%s; enter;", __func__);

  uint8_t recvBuffer[1024];
  int32_t recvBufferActualSize = 0;
  ScopedByteArrayRW bytes(e, data_cmd);
  bool rslt = false;

  rslt = NfcStExtensions::getInstance().transceive(
      pipe_id, hciCmd, bytes.size(), reinterpret_cast<uint8_t *>(&bytes[0]),
      recvBufferActualSize, recvBuffer);

  jbyteArray result = e->NewByteArray(recvBufferActualSize);
  if (result != NULL) {
    e->SetByteArrayRegion(result, 0, recvBufferActualSize, (jbyte *)recvBuffer);
  }

  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
      "%s; exit: received data length =%d", __func__, recvBufferActualSize);
  return result;
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_disconnectGate
**
** Description:     Connect/disconnect the secure element.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static void nativeNfcStExtensions_disconnectGate(JNIEnv *e, jobject,
                                                 jint pipe_id) {
  NfcStExtensions::getInstance().disconnectGate(pipe_id);
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_setNciConfig
**
** Description:     Set a NCI parameter.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static void nativeNfcStExtensions_setNciConfig(JNIEnv *e, jobject,
                                               jint param_id, jbyteArray param,
                                               jint length) {
  ScopedByteArrayRW bytes(e, param);
  NfcStExtensions::getInstance().setNciConfig(
      param_id, reinterpret_cast<uint8_t *>(&bytes[0]), length);
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_getNciConfig
**
** Description:     Set a NCI parameter.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static jbyteArray nativeNfcStExtensions_getNciConfig(JNIEnv *e, jobject,
                                                     jint param_id) {
  uint16_t recvBufferActualSize = 0;
  uint8_t recvBuffer[256];

  NfcStExtensions::getInstance().getNciConfig(param_id, recvBuffer,
                                              recvBufferActualSize);

  jbyteArray result = e->NewByteArray(recvBufferActualSize);
  if (result != NULL) {
    e->SetByteArrayRegion(result, 0, recvBufferActualSize, (jbyte *)recvBuffer);
  }

  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
      "%s; exit: received data length =%d", __func__, recvBufferActualSize);
  return result;
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_getAvailableHciHostList
**
** Description:     Set a NCI parameter.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static int nativeNfcStExtensions_getAvailableHciHostList(JNIEnv *e, jobject,
                                                         jbyteArray nfceeId,
                                                         jbyteArray conInfo) {
  uint8_t nfceeIdArray[3];
  uint8_t conInfoArray[3];
  int num = 0;

  num = NfcStExtensions::getInstance().getAvailableHciHostList(nfceeIdArray,
                                                               conInfoArray);

  e->SetByteArrayRegion(nfceeId, 0, num, (jbyte *)nfceeIdArray);
  e->SetByteArrayRegion(conInfo, 0, num, (jbyte *)conInfoArray);
  return num;
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_sendPropSetConfig
**
** Description:     Set a NCI parameter.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:
**
*******************************************************************************/
static void nativeNfcStExtensions_sendPropSetConfig(JNIEnv *e, jobject,
                                                    jint configSubSetId,
                                                    jint paramId,
                                                    jbyteArray param,
                                                    jint length) {
  ScopedByteArrayRW bytes(e, param);
  NfcStExtensions::getInstance().sendPropSetConfig(
      configSubSetId, paramId, reinterpret_cast<uint8_t *>(&bytes[0]), length);
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_sendPropGetConfig
**
** Description:     Set a NCI parameter.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Byte array containing prop config
**
*******************************************************************************/
static jbyteArray nativeNfcStExtensions_sendPropGetConfig(JNIEnv *e, jobject,
                                                          jint configSubSetId,
                                                          jint paramId) {
  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf("%s; enter;", __func__);

  uint16_t recvBufferActualSize = 0;
  uint8_t recvBuffer[256];

  NfcStExtensions::getInstance().sendPropGetConfig(
      configSubSetId, paramId, recvBuffer, recvBufferActualSize);

  jbyteArray result = e->NewByteArray(recvBufferActualSize);
  if (result != NULL) {
    e->SetByteArrayRegion(result, 0, recvBufferActualSize, (jbyte *)recvBuffer);
  }

  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
      "%s; exit: received data length =%hu", __func__, recvBufferActualSize);
  return result;
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_sendPropTestCmd
**
** Description:     Set a NCI parameter.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         byte array containing result of test cmd
**
*******************************************************************************/
static jbyteArray nativeNfcStExtensions_sendPropTestCmd(JNIEnv *e, jobject,
                                                        jint OID, jint subCode,
                                                        jbyteArray paramTx,
                                                        jint lengthTx) {
  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf("%s; enter;", __func__);
  uint16_t recvBufferActualSize = 0;
  uint8_t recvBuffer[256];

  ScopedByteArrayRW bytes(e, paramTx);
  NfcStExtensions::getInstance().sendPropTestCmd(
      OID, subCode, reinterpret_cast<uint8_t *>(&bytes[0]), lengthTx,
      recvBuffer, recvBufferActualSize);

  jbyteArray result = e->NewByteArray(recvBufferActualSize);
  if (result != NULL) {
    e->SetByteArrayRegion(result, 0, recvBufferActualSize, (jbyte *)recvBuffer);
  }

  DLOG_IF(INFO, nfc_debug_enabled) << StringPrintf(
      "%s; exit: received data length =%d", __func__, recvBufferActualSize);
  return result;
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_getAvailableHciHostList
**
** Description:     Set a NCI parameter.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
bool nativeNfcStExtensions_rawRfAuth(JNIEnv *e, jobject, jboolean enable) {
  return NfcStExtensions::getInstance().sendRawRfCmd(PROP_AUTH_RF_RAW_MODE_CMD,
                                                     (bool)enable);
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_rawRfMode
**
** Description:     Set a NCI parameter.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
bool nativeNfcStExtensions_rawRfMode(JNIEnv *e, jobject, jboolean enable) {
  return NfcStExtensions::getInstance().sendRawRfCmd(PROP_CTRL_RF_RAW_MODE_CMD,
                                                     (bool)enable);
}

/*******************************************************************************
**
** Function:        nativeNfcStExtensions_rawJniSeq
**
** Description:     Set a NCI parameter.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
extern void nativeNfcTag_setInRawJniSeq(bool status);
jbyteArray nativeNfcStExtensions_rawJniSeq(JNIEnv *e, jobject o, jint i,
                                           jbyteArray ba) {
  bool ret;
  const size_t retBufferMaxSize = 8192;
  uint8_t retBuffer[retBufferMaxSize];
  size_t retBufferActualSize = 0;
  ScopedByteArrayRW bytes(e, ba);

  nativeNfcTag_setInRawJniSeq(true);
  ret = rawJniSeq(i, reinterpret_cast<uint8_t *>(&bytes[0]), bytes.size(),
                  retBuffer, retBufferMaxSize, &retBufferActualSize);
  nativeNfcTag_setInRawJniSeq(false);
  if (ret == 0) {
    jbyteArray result = e->NewByteArray(retBufferActualSize);
    if (result != NULL) {
      e->SetByteArrayRegion(result, 0, retBufferActualSize, (jbyte *)retBuffer);
    }
    return result;
  } else {
    return NULL;
  }
}

/*****************************************************************************
**
** Description:     JNI functions
**
*****************************************************************************/
static JNINativeMethod gMethods[] = {
    {"getFirmwareVersion", "()[B",
     (void *)nativeNfcStExtensions_getFirmwareVersion},
    {"getCRCConfiguration", "()[B",
     (void *)nativeNfcStExtensions_getCRCConfiguration},
    {"getHWVersion", "()[B", (void *)nativeNfcStExtensions_getHWVersion},
    {"getSWVersion", "()[B", (void *)nativeNfcStExtensions_getSWVersion},
    {"isUiccConnected", "()Z", (void *)nativeNfcStExtensions_isUiccConnected},
    {"iseSEConnected", "()Z", (void *)nativeNfcStExtensions_iseSEConnected},
    {"isSEConnected", "(I)Z", (void *)nativeNfcStExtensions_isSEConnected},
    {"loopback", "()I", (void *)nativeNfcStExtensions_loopback},
    {"getHceUserProp", "()I", (void *)nativeNfcStExtensions_getHceUserProp},
    {"setRfConfiguration", "(I[B)V",
     (void *)nativeNfcStExtensions_setRfConfiguration},
    {"getRfConfiguration", "([B)I",
     (void *)nativeNfcStExtensions_getRfConfiguration},
    {"setRfBitmap", "(I)V", (void *)nativeNfcStExtensions_setRfBitmap},
    {"updatePipesInfo", "()I", (void *)nativeNfcStExtensions_updatePipesInfo},
    {"setDefaultOffHostRoute", "(I)V",
     (void *)nativeNfcStExtensions_setDefaultOffHostRoute},
    {"getDefaultOffHostRoute", "()I",
     (void *)nativeNfcStExtensions_getDefaultOffHostRoute},
    {"getProprietaryConfigSettings", "(III)Z",
     (void *)nativeNfcStExtensions_getProprietaryConfigSettings},
    {"setProprietaryConfigSettings", "(IIIZ)V",
     (void *)nativeNfcStExtensions_setProprietaryConfigSettings},
    {"getPipesList", "(I[B)I", (void *)nativeNfcStExtensions_getPipesList},
    {"getPipeInfo", "(II[B)V", (void *)nativeNfcStExtensions_getPipeInfo},
    {"getATR", "()[B", (void *)nativeNfcStExtensions_getAtr},
    {"EnableSE", "(IZ)Z", (void *)nativeNfcStExtensions_EnableSE},
    {"connectEE", "(I)Z", (void *)nativeNfcStExtensions_connectEE},
    {"transceiveEE", "(I[B)[B", (void *)nativeNfcStExtensions_transceiveEE},
    {"disconnectEE", "(I)Z", (void *)nativeNfcStExtensions_disconnectEE},
    {"connectGate", "(II)I", (void *)nativeNfcStExtensions_connectGate},
    {"transceive", "(II[B)[B", (void *)nativeNfcStExtensions_transceive},
    {"disconnectGate", "(I)V", (void *)nativeNfcStExtensions_disconnectGate},
    {"setNciConfig", "(I[BI)V", (void *)nativeNfcStExtensions_setNciConfig},
    {"getNciConfig", "(I)[B", (void *)nativeNfcStExtensions_getNciConfig},
    {"getAvailableHciHostList", "([B[B)I",
     (void *)nativeNfcStExtensions_getAvailableHciHostList},
    {"sendPropSetConfig", "(II[BI)V",
     (void *)nativeNfcStExtensions_sendPropSetConfig},
    {"sendPropGetConfig", "(II)[B",
     (void *)nativeNfcStExtensions_sendPropGetConfig},
    {"sendPropTestCmd", "(II[BI)[B",
     (void *)nativeNfcStExtensions_sendPropTestCmd},
    {"getCustomerData", "()[B", (void *)nativeNfcStExtensions_getCustomerData},
    {"rawRfAuth", "(Z)Z", (void *)nativeNfcStExtensions_rawRfAuth},
    {"rawRfMode", "(Z)Z", (void *)nativeNfcStExtensions_rawRfMode},
    {"rawJniSeq", "(I[B)[B", (void *)nativeNfcStExtensions_rawJniSeq},
};

/*******************************************************************************
**
** Function:        register_com_android_nfc_NativeNfcStExtensions
**
** Description:     Register JNI functions with Java Virtual Machine.
**                  e: Environment of JVM.
**
** Returns:         Status of registration.
**
*******************************************************************************/
int register_com_android_nfc_NativeNfcStExtensions(JNIEnv *e) {
  return jniRegisterNativeMethods(e, gNativeNfcStExtensionsClassName, gMethods,
                                  NELEM(gMethods));
}

}  // namespace android
