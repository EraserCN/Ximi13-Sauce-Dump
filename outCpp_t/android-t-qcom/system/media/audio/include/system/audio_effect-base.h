// This file is autogenerated by hidl-gen. Do not edit manually.
// Source: android.hardware.audio.effect@7.0
// Location: hardware/interfaces/audio/effect/7.0/

#ifndef HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_EFFECT_V7_0_EXPORTED_CONSTANTS_H_
#define HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_EFFECT_V7_0_EXPORTED_CONSTANTS_H_

#ifdef __cplusplus
extern "C" {
#endif

enum {
    EFFECT_FLAG_TYPE_SHIFT = 0,
    EFFECT_FLAG_TYPE_SIZE = 3,
    EFFECT_FLAG_TYPE_MASK = 7 /* ((1 << TYPE_SIZE) - 1) << TYPE_SHIFT */,
    EFFECT_FLAG_TYPE_INSERT = 0 /* 0 << TYPE_SHIFT */,
    EFFECT_FLAG_TYPE_AUXILIARY = 1 /* 1 << TYPE_SHIFT */,
    EFFECT_FLAG_TYPE_REPLACE = 2 /* 2 << TYPE_SHIFT */,
    EFFECT_FLAG_TYPE_PRE_PROC = 3 /* 3 << TYPE_SHIFT */,
    EFFECT_FLAG_TYPE_POST_PROC = 4 /* 4 << TYPE_SHIFT */,
    EFFECT_FLAG_INSERT_SHIFT = 3 /* TYPE_SHIFT + TYPE_SIZE */,
    EFFECT_FLAG_INSERT_SIZE = 3,
    EFFECT_FLAG_INSERT_MASK = 56 /* ((1 << INSERT_SIZE) - 1) << INSERT_SHIFT */,
    EFFECT_FLAG_INSERT_ANY = 0 /* 0 << INSERT_SHIFT */,
    EFFECT_FLAG_INSERT_FIRST = 8 /* 1 << INSERT_SHIFT */,
    EFFECT_FLAG_INSERT_LAST = 16 /* 2 << INSERT_SHIFT */,
    EFFECT_FLAG_INSERT_EXCLUSIVE = 24 /* 3 << INSERT_SHIFT */,
    EFFECT_FLAG_VOLUME_SHIFT = 6 /* INSERT_SHIFT + INSERT_SIZE */,
    EFFECT_FLAG_VOLUME_SIZE = 3,
    EFFECT_FLAG_VOLUME_MASK = 448 /* ((1 << VOLUME_SIZE) - 1) << VOLUME_SHIFT */,
    EFFECT_FLAG_VOLUME_CTRL = 64 /* 1 << VOLUME_SHIFT */,
    EFFECT_FLAG_VOLUME_IND = 128 /* 2 << VOLUME_SHIFT */,
    EFFECT_FLAG_VOLUME_MONITOR = 192 /* 3 << VOLUME_SHIFT */,
    EFFECT_FLAG_VOLUME_NONE = 0 /* 0 << VOLUME_SHIFT */,
    EFFECT_FLAG_DEVICE_SHIFT = 9 /* VOLUME_SHIFT + VOLUME_SIZE */,
    EFFECT_FLAG_DEVICE_SIZE = 3,
    EFFECT_FLAG_DEVICE_MASK = 3584 /* ((1 << DEVICE_SIZE) - 1) << DEVICE_SHIFT */,
    EFFECT_FLAG_DEVICE_IND = 512 /* 1 << DEVICE_SHIFT */,
    EFFECT_FLAG_DEVICE_NONE = 0 /* 0 << DEVICE_SHIFT */,
    EFFECT_FLAG_INPUT_SHIFT = 12 /* DEVICE_SHIFT + DEVICE_SIZE */,
    EFFECT_FLAG_INPUT_SIZE = 2,
    EFFECT_FLAG_INPUT_MASK = 12288 /* ((1 << INPUT_SIZE) - 1) << INPUT_SHIFT */,
    EFFECT_FLAG_INPUT_DIRECT = 4096 /* 1 << INPUT_SHIFT */,
    EFFECT_FLAG_INPUT_PROVIDER = 8192 /* 2 << INPUT_SHIFT */,
    EFFECT_FLAG_INPUT_BOTH = 12288 /* 3 << INPUT_SHIFT */,
    EFFECT_FLAG_OUTPUT_SHIFT = 14 /* INPUT_SHIFT + INPUT_SIZE */,
    EFFECT_FLAG_OUTPUT_SIZE = 2,
    EFFECT_FLAG_OUTPUT_MASK = 49152 /* ((1 << OUTPUT_SIZE) - 1) << OUTPUT_SHIFT */,
    EFFECT_FLAG_OUTPUT_DIRECT = 16384 /* 1 << OUTPUT_SHIFT */,
    EFFECT_FLAG_OUTPUT_PROVIDER = 32768 /* 2 << OUTPUT_SHIFT */,
    EFFECT_FLAG_OUTPUT_BOTH = 49152 /* 3 << OUTPUT_SHIFT */,
    EFFECT_FLAG_HW_ACC_SHIFT = 16 /* OUTPUT_SHIFT + OUTPUT_SIZE */,
    EFFECT_FLAG_HW_ACC_SIZE = 2,
    EFFECT_FLAG_HW_ACC_MASK = 196608 /* ((1 << HW_ACC_SIZE) - 1) << HW_ACC_SHIFT */,
    EFFECT_FLAG_HW_ACC_SIMPLE = 65536 /* 1 << HW_ACC_SHIFT */,
    EFFECT_FLAG_HW_ACC_TUNNEL = 131072 /* 2 << HW_ACC_SHIFT */,
    EFFECT_FLAG_AUDIO_MODE_SHIFT = 18 /* HW_ACC_SHIFT + HW_ACC_SIZE */,
    EFFECT_FLAG_AUDIO_MODE_SIZE = 2,
    EFFECT_FLAG_AUDIO_MODE_MASK = 786432 /* ((1 << AUDIO_MODE_SIZE) - 1) << AUDIO_MODE_SHIFT */,
    EFFECT_FLAG_AUDIO_MODE_IND = 262144 /* 1 << AUDIO_MODE_SHIFT */,
    EFFECT_FLAG_AUDIO_MODE_NONE = 0 /* 0 << AUDIO_MODE_SHIFT */,
    EFFECT_FLAG_AUDIO_SOURCE_SHIFT = 20 /* AUDIO_MODE_SHIFT + AUDIO_MODE_SIZE */,
    EFFECT_FLAG_AUDIO_SOURCE_SIZE = 2,
    EFFECT_FLAG_AUDIO_SOURCE_MASK = 3145728 /* ((1 << AUDIO_SOURCE_SIZE) - 1) << AUDIO_SOURCE_SHIFT */,
    EFFECT_FLAG_AUDIO_SOURCE_IND = 1048576 /* 1 << AUDIO_SOURCE_SHIFT */,
    EFFECT_FLAG_AUDIO_SOURCE_NONE = 0 /* 0 << AUDIO_SOURCE_SHIFT */,
    EFFECT_FLAG_OFFLOAD_SHIFT = 22 /* AUDIO_SOURCE_SHIFT + AUDIO_SOURCE_SIZE */,
    EFFECT_FLAG_OFFLOAD_SIZE = 1,
    EFFECT_FLAG_OFFLOAD_MASK = 4194304 /* ((1 << OFFLOAD_SIZE) - 1) << OFFLOAD_SHIFT */,
    EFFECT_FLAG_OFFLOAD_SUPPORTED = 4194304 /* 1 << OFFLOAD_SHIFT */,
    EFFECT_FLAG_NO_PROCESS_SHIFT = 23 /* OFFLOAD_SHIFT + OFFLOAD_SIZE */,
    EFFECT_FLAG_NO_PROCESS_SIZE = 1,
    EFFECT_FLAG_NO_PROCESS_MASK = 8388608 /* ((1 << NO_PROCESS_SIZE) - 1) << NO_PROCESS_SHIFT */,
    EFFECT_FLAG_NO_PROCESS = 8388608 /* 1 << NO_PROCESS_SHIFT */,
    //MIUI ADD
    EFFECT_FLAG_AUDIO_STANDBY_SHIFT = 24,
    EFFECT_FLAG_AUDIO_STANDBY_SIZE = 1,
    EFFECT_FLAG_AUDIO_STANDBY_MASK = 16777216, // (((1 << EFFECT_FLAG_AUDIO_STANDBY_SIZE) -1) \ << EFFECT_FLAG_AUDIO_STANDBY_SHIFT)
    EFFECT_FLAG_AUDIO_STANDBY_IND = 16777216, // (1 << EFFECT_FLAG_AUDIO_STANDBY_SHIFT)
    EFFECT_FLAG_AUDIO_STANDBY_NONE = 0, // (0 << EFFECT_FLAG_AUDIO_STANDBY_SHIFT)
    EFFECT_FLAG_APP_NAME_SHIFT = 25, //  (EFFECT_FLAG_AUDIO_STANDBY_SHIFT + EFFECT_FLAG_AUDIO_STANDBY_SIZE)
    EFFECT_FLAG_APP_NAME_SIZE = 1,
    EFFECT_FLAG_APP_NAME_MASK = 33554432, // (((1 << EFFECT_FLAG_APP_NAME_SIZE) -1) \  << EFFECT_FLAG_APP_NAME_SHIFT)
    EFFECT_FLAG_APP_NAME_IND = 33554432, // (1 << EFFECT_FLAG_APP_NAME_SHIFT)
    EFFECT_FLAG_APP_NAME_NONE = 0, // (0 << EFFECT_FLAG_APP_NAME_SHIFT)
    EFFECT_FLAG_STREAM_VOLUME_SHIFT = 26, //  (EFFECT_FLAG_APP_NAME_SHIFT + EFFECT_FLAG_APP_NAME_SIZE)
    EFFECT_FLAG_STREAM_VOLUME_SIZE = 1,
    EFFECT_FLAG_STREAM_VOLUME_MASK = 67108864, //  (((1 << EFFECT_FLAG_STREAM_VOLUME_SIZE) -1) \ << EFFECT_FLAG_STREAM_VOLUME_SHIFT)
    EFFECT_FLAG_STREAM_VOLUME_IND = 67108864, //  (1 << EFFECT_FLAG_STREAM_VOLUME_SHIFT)
    EFFECT_FLAG_STREAM_VOLUME_NONE = 0, // (0 << EFFECT_FLAG_STREAM_VOLUME_SHIFT)
};

typedef enum {
    EFFECT_BUFFER_ACCESS_WRITE = 0,
    EFFECT_BUFFER_ACCESS_READ = 1 /* ::android::hardware::audio::effect::V7_0::EffectBufferAccess.ACCESS_WRITE implicitly + 1 */,
    EFFECT_BUFFER_ACCESS_ACCUMULATE = 2 /* ::android::hardware::audio::effect::V7_0::EffectBufferAccess.ACCESS_READ implicitly + 1 */,
} effect_buffer_access_e;

typedef enum {
    EFFECT_FEATURE_AUX_CHANNELS = 0,
    EFFECT_FEATURE_CNT = 1 /* ::android::hardware::audio::effect::V7_0::EffectFeature.AUX_CHANNELS implicitly + 1 */,
} effect_feature_e;

#ifdef __cplusplus
}
#endif

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_EFFECT_V7_0_EXPORTED_CONSTANTS_H_
