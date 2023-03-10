/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_xiaomi_engine_MiCamAlgoInterfaceJNI */

#ifndef _Included_com_xiaomi_engine_MiCamAlgoInterfaceJNI
#define _Included_com_xiaomi_engine_MiCamAlgoInterfaceJNI
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_xiaomi_engine_MiCamAlgoInterfaceJNI
 * Method:    init
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_xiaomi_engine_MiCamAlgoInterfaceJNI_init(JNIEnv *, jclass, jstring);

/*
 * Class:     com_xiaomi_engine_MiCamAlgoInterfaceJNI
 * Method:    init
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_xiaomi_engine_MiCamAlgoInterfaceJNI_setMiViInfo(JNIEnv *, jclass,
                                                                                jstring);

/*
 * Class:     com_xiaomi_engine_MiCamAlgoInterfaceJNI
 * Method:    createSessionWithSurfaces
 * Signature:
 * (Lcom/xiaomi/engine/BufferFormat;Ljava/util/List;Lcom/xiaomi/engine/TaskSession/SessionStatusCallback;)J
 */
JNIEXPORT jlong JNICALL Java_com_xiaomi_engine_MiCamAlgoInterfaceJNI_createSessionWithSurfaces(
    JNIEnv *, jclass, jobject, jobject, jobject);

/*
 * Class:     com_xiaomi_engine_MiCamAlgoInterfaceJNI
 * Method:    createSessionByOutputConfigurations
 * Signature:
 * (Lcom/xiaomi/engine/BufferFormat;Ljava/util/List;Lcom/xiaomi/engine/TaskSession/SessionStatusCallback;)J
 */
JNIEXPORT jlong JNICALL
Java_com_xiaomi_engine_MiCamAlgoInterfaceJNI_createSessionByOutputConfigurations(JNIEnv *, jclass,
                                                                                 jobject, jobject,
                                                                                 jobject);

/*
 * Class:     com_xiaomi_engine_MiCamAlgoInterfaceJNI
 * Method:    processFrame
 * Signature: (JLcom/xiaomi/engine/FrameData;Lcom/xiaomi/engine/TaskSession/FrameCallback;)I
 */
JNIEXPORT jint JNICALL Java_com_xiaomi_engine_MiCamAlgoInterfaceJNI_processFrame(JNIEnv *, jclass,
                                                                                 jlong, jobject,
                                                                                 jobject);

/*
 * Class:     com_xiaomi_engine_MiCamAlgoInterfaceJNI
 * Method:    processFrameWithSync
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_xiaomi_engine_MiCamAlgoInterfaceJNI_processFrameWithSync(
    JNIEnv *env, jclass obj, jlong sessionID, jobject frameDataList, jobject resultImage,
    jint algo_type);

JNIEXPORT jint JNICALL Java_com_xiaomi_engine_MiCamAlgoInterfaceJNI_preProcess(
    JNIEnv *env, jclass obj, jlong sessionId, jobject data);

/*
 * Class:     com_xiaomi_engine_MiCamAlgoInterfaceJNI
 * Method:    destroySession
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_xiaomi_engine_MiCamAlgoInterfaceJNI_destroySession(JNIEnv *, jclass,
                                                                                   jlong);

/*
 * Class:     com_xiaomi_engine_MiCamAlgoInterfaceJNI
 * Method:    flush
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_xiaomi_engine_MiCamAlgoInterfaceJNI_flush(JNIEnv *, jclass, jlong);

  /*
   * Class:     com_xiaomi_engine_MiCamAlgoInterfaceJNI
   * Method:    flush
   * Signature: (J)I
   */
JNIEXPORT jint JNICALL Java_com_xiaomi_engine_MiCamAlgoInterfaceJNI_quickFinish
  (JNIEnv *, jclass, jlong, jlong, jboolean);

/*
 * Class:     com_xiaomi_engine_MiCamAlgoInterfaceJNI
 * Method:    deInit
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_xiaomi_engine_MiCamAlgoInterfaceJNI_deInit(JNIEnv *, jclass);

/*
 * Class:     com_xiaomi_engine_MiCamAlgoInterfaceJNI
 * Method:    getVersionCode
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_xiaomi_engine_MiCamAlgoInterfaceJNI_getVersionCode(JNIEnv *,
                                                                                   jclass);
#ifdef __cplusplus
}
#endif
#endif
