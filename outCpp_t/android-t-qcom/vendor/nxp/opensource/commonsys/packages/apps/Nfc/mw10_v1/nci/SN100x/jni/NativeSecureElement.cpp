/******************************************************************************
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*  http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*  Copyright 2018-2019 NXP
*
******************************************************************************/

#include <android-base/stringprintf.h>
#include <base/logging.h>
#include "PowerSwitch.h"
#include "RoutingManager.h"
#include <nativehelper/ScopedPrimitiveArray.h>
#include <nativehelper/ScopedUtfChars.h>
#include <nativehelper/ScopedLocalRef.h>
#include "JavaClassConstants.h"
#include "NfcJniUtil.h"
#include "config.h"
#include "SecureElement.h"
#include "NfcAdaptation.h"
#include "NativeJniExtns.h"
using android::base::StringPrintf;

namespace android
{
static const int EE_ERROR_INIT = -3;
extern bool nfcManager_isNfcActive();
/*******************************************************************************
**
** Function:        nativeNfcSecureElement_doOpenSecureElementConnection
**
** Description:     Connect to the secure element.
**                  e: JVM environment.
**                  o: Java object.
**
** Returns:         Handle of secure element.  values < 0 represent failure.
**
*******************************************************************************/
static jint nativeNfcSecureElement_doOpenSecureElementConnection (JNIEnv*, jobject)
{
    LOG(INFO) << StringPrintf("%s: Enter; ", __func__);
    bool stat = false;
    const int32_t recvBufferMaxSize = 1024;
    uint8_t recvBuffer [recvBufferMaxSize];
    int32_t recvBufferActualSize = 0;

    jint secElemHandle = EE_ERROR_INIT;
    NFCSTATUS status = NFCSTATUS_FAILED;
    SecureElement &se = SecureElement::getInstance();
    se.mModeSetNtfstatus = NFA_STATUS_FAILED;

    NativeJniExtns::getInstance().notifyNfcEvent(__func__);
    /* Tell the controller to power up to get ready for sec elem operations */
    PowerSwitch::getInstance ().setLevel (PowerSwitch::FULL_POWER);
    PowerSwitch::getInstance ().setModeOn (PowerSwitch::SE_CONNECTED);

    /* If controller is not routing AND there is no pipe connected,
           then turn on the sec elem */
    stat = se.activate(SecureElement::ESE_ID); // It is to get the current activated handle.

    if((stat) && (nfcFL.eseFL._NCI_NFCEE_PWR_LINK_CMD))
    {
       status = se.setNfccPwrConfig(se.POWER_ALWAYS_ON|se.COMM_LINK_ACTIVE);
    }
    if(status != NFA_STATUS_OK)
    {
      LOG(INFO) << StringPrintf("%s: power link command failed", __func__);
      stat =false;
    }
    else
    {
       stat = se.SecEle_Modeset(se.NFCEE_ENABLE);
       if(se.mModeSetNtfstatus != NFA_STATUS_OK)
       {
         stat = false;
         LOG(INFO) << StringPrintf("%s: Mode set ntf STATUS_FAILED", __func__);

         SyncEventGuard guard (se.mEERecoveryComplete);
         {
           se.mEERecoveryComplete.wait();
           LOG(INFO) << StringPrintf("%s: Recovery complete", __func__);
         }
         if(se.mErrorRecovery)
         {
           stat = true;
         }
       }
       if(stat == true)
       {
         se.mIsWiredModeOpen = true;
         stat = se.apduGateReset(se.mActiveEeHandle, recvBuffer, &recvBufferActualSize);
        if (stat)
        {
            secElemHandle = se.mActiveEeHandle;
        }
       }
    }

    /* if code fails to connect to the secure element, and nothing is active, then
     * tell the controller to power down
     */
    if ((!stat) && (! PowerSwitch::getInstance ().setModeOff (PowerSwitch::SE_CONNECTED)))
    {
        LOG(INFO) << StringPrintf("%s: stat fails; ", __func__);
        PowerSwitch::getInstance ().setLevel (PowerSwitch::LOW_POWER);
        se.deactivate(SecureElement::ESE_ID);
        se.mIsWiredModeOpen = false;
        stat = false;
    }
    LOG(INFO) << StringPrintf("%s: exit; return handle=0x%X", __func__, secElemHandle);
    return secElemHandle;
}


/*******************************************************************************
**
** Function:        nativeNfcSecureElement_doDisconnectSecureElementConnection
**
** Description:     Disconnect from the secure element.
**                  e: JVM environment.
**                  o: Java object.
**                  handle: Handle of secure element.
**
** Returns:         True if ok.
**
*******************************************************************************/
static jboolean nativeNfcSecureElement_doDisconnectSecureElementConnection (JNIEnv*, jobject, jint handle)
{
    LOG(INFO) << StringPrintf("%s: enter; handle=0x%04x", __func__, handle);
    bool stat = false;
    NFCSTATUS status = NFCSTATUS_FAILED;
    SecureElement &se = SecureElement::getInstance();

    if(!se.mIsWiredModeOpen)
         return false;
     /* release any pending transceive wait */
    se.releasePendingTransceive();

    status = se.setNfccPwrConfig(se.POWER_ALWAYS_ON);
    if(status != NFA_STATUS_OK)
    {
        LOG(INFO) << StringPrintf("%s: power link command failed", __func__);
    }
    else
    {
        status = se.sendEvent(SecureElement::EVT_END_OF_APDU_TRANSFER);
        if(status == NFA_STATUS_OK)
            stat = true;
    }
    se.mIsWiredModeOpen = false;

    /* if nothing is active after this, then tell the controller to power down */
    if (! PowerSwitch::getInstance ().setModeOff (PowerSwitch::SE_CONNECTED))
        PowerSwitch::getInstance ().setLevel (PowerSwitch::LOW_POWER);
    LOG(INFO) << StringPrintf("%s: exit", __func__);
    return stat ? JNI_TRUE : JNI_FALSE;
}
/*******************************************************************************
**
** Function:        nativeNfcSecureElement_doResetForEseCosUpdate
**
** Description:     Reset the secure element.
**                  e: JVM environment.
**                  o: Java object.
**                  handle: Handle of secure element.
**
** Returns:         True if ok.
**
*******************************************************************************/
static jboolean nativeNfcSecureElement_doResetForEseCosUpdate(JNIEnv*, jobject,
                                                              jint handle) {
  bool stat = false;
  int ret = -1;
  NfcAdaptation& theInstance = NfcAdaptation::GetInstance();
  tHAL_NFC_ENTRY* halFuncEntries = theInstance.GetHalEntryFuncs ();
  nfc_nci_IoctlInOutData_t inpOutData;
  inpOutData.inp.level = NCI_ESE_HARD_RESET_IOCTL;
  LOG(INFO) << StringPrintf("%s: Entry", __func__);
  if(NULL == halFuncEntries) {
    LOG(INFO) << StringPrintf("%s: halFuncEntries is NULL", __func__);
  } else {
    ret = halFuncEntries->ioctl(HAL_NFC_IOCTL_ESE_HARD_RESET, (void*)&inpOutData);
    if(ret < 0) {
      LOG(INFO) << StringPrintf("%s: IOCTL failed", __func__);
    } else {
      stat = true;
    }
  }
  LOG(INFO) << StringPrintf("%s: exit", __func__);
  return stat;
}

/*******************************************************************************
**
** Function:        nativeNfcSecureElement_doGetAtr
**
** Description:     GetAtr from the connected eSE.
**                  e: JVM environment.
**                  o: Java object.
**                  handle: Handle of secure element.
**
** Returns:         Buffer of received data.
**
*******************************************************************************/
static jbyteArray nativeNfcSecureElement_doGetAtr (JNIEnv* e, jobject, jint handle)
{
    bool stat = false;
    const int32_t recvBufferMaxSize = 1024;
    uint8_t recvBuffer [recvBufferMaxSize];
    int32_t recvBufferActualSize = 0;
    LOG(INFO) << StringPrintf("%s: enter; handle=0x%04x", __func__, handle);
    SecureElement &se = SecureElement::getInstance();

    stat = se.getAtr(recvBuffer, &recvBufferActualSize);

    //copy results back to java
    jbyteArray result = e->NewByteArray(recvBufferActualSize);
    if (result != NULL) {
        e->SetByteArrayRegion(result, 0, recvBufferActualSize, (jbyte *) recvBuffer);
    }

    LOG(INFO) << StringPrintf("%s: exit: recv len=%d", __func__, recvBufferActualSize);

    return result;
}

/*******************************************************************************
**
** Function:        nativeNfcSecureElement_doTransceive
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
static jbyteArray nativeNfcSecureElement_doTransceive (JNIEnv* e, jobject, jint handle, jbyteArray data)
{
    const int32_t recvBufferMaxSize = 0x8800;//1024; 34k
    uint8_t recvBuffer [recvBufferMaxSize];
    int32_t recvBufferActualSize = 0;
    ScopedByteArrayRW bytes(e, data);
    LOG(INFO) << StringPrintf("%s: enter; handle=0x%X; buf len=%zu", __func__, handle, bytes.size());

    SecureElement &se = SecureElement::getInstance();
    if(!se.mIsWiredModeOpen)
        return NULL;

    se.transceive(reinterpret_cast<uint8_t*>(&bytes[0]), bytes.size(), recvBuffer, recvBufferMaxSize, recvBufferActualSize, se.SmbTransceiveTimeOutVal);

    //copy results back to java
    jbyteArray result = e->NewByteArray(recvBufferActualSize);
    if (result != NULL)
    {
        e->SetByteArrayRegion(result, 0, recvBufferActualSize, (jbyte *) recvBuffer);
    }

    LOG(INFO) << StringPrintf("%s: exit: recv len=%d", __func__, recvBufferActualSize);
    return result;
}
/*******************************************************************************
**
** Function:        nfcManager_doactivateSeInterface
**
** Description:     Activate SecureElement Interface
**
** Returns:         Success/Failure
**                  Success = 0x00
**                  Failure = 0x03
**
*******************************************************************************/
static jint nfcManager_doactivateSeInterface(JNIEnv* e, jobject o) {
  jint ret = NFA_STATUS_FAILED;
  tNFA_STATUS status = NFA_STATUS_FAILED;
  SecureElement& se = SecureElement::getInstance();
  se.mModeSetNtfstatus = NFA_STATUS_FAILED;

  LOG(INFO) << StringPrintf("%s: enter", __func__);

  if (!nfcManager_isNfcActive() || (!nfcFL.eseFL._NCI_NFCEE_PWR_LINK_CMD)) {
    LOG(INFO) << StringPrintf("%s: Not supported", __func__);
    return ret;
  }
  if (se.mIsSeIntfActivated) {
    LOG(INFO) << StringPrintf("%s: Already activated", __func__);
    return NFA_STATUS_OK;
  }
  status = se.setNfccPwrConfig(se.POWER_ALWAYS_ON | se.COMM_LINK_ACTIVE);
  if (status == NFA_STATUS_OK) {
    status = se.SecEle_Modeset(se.NFCEE_ENABLE);
    if (se.mModeSetNtfstatus != NFA_STATUS_OK) {
      LOG(INFO) << StringPrintf("%s: Mode set ntf STATUS_FAILED", __func__);
      SyncEventGuard guard(se.mEERecoveryComplete);
      if (se.mEERecoveryComplete.wait(NFC_CMD_TIMEOUT)) {
        LOG(INFO) << StringPrintf("%s: Recovery complete", __func__);
        ret = NFA_STATUS_OK;
      }
    } else {
      ret = NFA_STATUS_OK;
    }
  } else {
    LOG(INFO) << StringPrintf("%s: power link command failed", __func__);
  }

  if (ret == NFA_STATUS_OK) se.mIsSeIntfActivated = true;
  LOG(INFO) << StringPrintf("%s: Exit", __func__);
  return ret;
}
/*******************************************************************************
**
** Function:        nfcManager_dodeactivateSeInterface
**
** Description:     Deactivate SecureElement Interface
**
** Returns:         Success/Failure
**                  Success = 0x00
**                  Failure = 0x03
**
*******************************************************************************/
static jint nfcManager_dodeactivateSeInterface(JNIEnv* e, jobject o) {
  jint ret = NFA_STATUS_FAILED;
  tNFA_STATUS status = NFA_STATUS_FAILED;
  SecureElement& se = SecureElement::getInstance();
  LOG(INFO) << StringPrintf("%s: enter", __func__);

  if (!nfcManager_isNfcActive() || (!nfcFL.eseFL._NCI_NFCEE_PWR_LINK_CMD)) {
    LOG(INFO) << StringPrintf("%s: Not supported", __func__);
    return ret;
  }
  if (!se.mIsSeIntfActivated) {
    LOG(INFO) << StringPrintf("%s: Already Deactivated or call activate first",
                              __func__);
    return NFA_STATUS_OK;
  }

  status = se.setNfccPwrConfig(se.POWER_ALWAYS_ON);
  if (status == NFA_STATUS_OK) {
    LOG(INFO) << StringPrintf("%s: power link command success", __func__);
    se.mIsSeIntfActivated = false;
    ret = NFA_STATUS_OK;
  }
  LOG(INFO) << StringPrintf("%s: Exit, status =0x02%u", __func__, status);
  return ret;
}
/*****************************************************************************
**
** Description:     JNI functions
**
*****************************************************************************/
static JNINativeMethod gMethods[] = {
    {"doNativeOpenSecureElementConnection", "()I",
     (void*)nativeNfcSecureElement_doOpenSecureElementConnection},
    {"doNativeDisconnectSecureElementConnection", "(I)Z",
     (void*)nativeNfcSecureElement_doDisconnectSecureElementConnection},
    {"doResetForEseCosUpdate", "(I)Z",
     (void*)nativeNfcSecureElement_doResetForEseCosUpdate},
    {"doTransceive", "(I[B)[B", (void*)nativeNfcSecureElement_doTransceive},
    {"doNativeGetAtr", "(I)[B", (void*)nativeNfcSecureElement_doGetAtr},
    {"doactivateSeInterface", "()I", (void*)nfcManager_doactivateSeInterface},
    {"dodeactivateSeInterface", "()I",
     (void*)nfcManager_dodeactivateSeInterface},
};

/*******************************************************************************
**
** Function:        register_com_android_nfc_NativeNfcSecureElement
**
** Description:     Regisgter JNI functions with Java Virtual Machine.
**                  e: Environment of JVM.
**
** Returns:         Status of registration.
**
*******************************************************************************/
int register_com_android_nfc_NativeNfcSecureElement(JNIEnv *e)
{
    return jniRegisterNativeMethods(e, gNativeNfcSecureElementClassName,
            gMethods, NELEM(gMethods));
}

} // namespace android
