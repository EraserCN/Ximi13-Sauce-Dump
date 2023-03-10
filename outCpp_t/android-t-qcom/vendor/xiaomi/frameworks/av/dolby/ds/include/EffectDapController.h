/******************************************************************************
 *  This program is protected under international and U.S. copyright laws as
 *  an unpublished work. This program is confidential and proprietary to the
 *  copyright owners. Reproduction or disclosure, in whole or in part, or the
 *  production of derivative works therefrom without the express permission of
 *  the copyright owners is prohibited.
 *
 *               Copyright (C) 2014-2022 by Dolby Laboratories.
 *                             All rights reserved.
 ******************************************************************************/

#ifndef INCLUDING_FROM_AUDIOFLINGER_H
    #error This header file should only be included from AudioFlinger.h
#endif

#ifndef DOLBY_EFFECT_DAP_CONTROLLER_H_
#define DOLBY_EFFECT_DAP_CONTROLLER_H_

#define DAX3_3POINT6 "DAX3_3.6"
#define DAX3_3POINT8 "DAX3_3.8"
#define PROPERTY_DAX_VERSION "ro.vendor.audio.dolby.dax.version"

class EffectDapController
{
public:
    static EffectDapController *instance()
    { return mInstance; }

    static bool isDapEffect(const sp<EffectBase> &effect)
    { return (memcmp(&effect->desc().type, &EFFECT_SL_IID_DAP, sizeof(effect_uuid_t)) == 0); }

    static std::vector<std::string> strSplit(std::string str, std::string sep);
    static int versionCompare(std::string version_1, std::string version_2);

    void effectCreated(const sp<EffectModule> &effect, const ThreadBase *thread);
    void effectReleased(const sp<EffectModule> &effect);
    void effectSuspended(const sp<EffectBase> &effect, bool suspend);
    void updateOffload(const ThreadBase *thread);
    void checkForBypass(const ThreadBase::ActiveTracks<PlaybackThread::Track> &tracks, audio_io_handle_t id);
    void updatePregain(ThreadBase::type_t   thread_type,
                       audio_io_handle_t    id,
                       audio_output_flags_t flags,
                       uint32_t             max_vol,
                       bool                 is_active = true);
    void checkAudioTracks(const ThreadBase::ActiveTracks<PlaybackThread::Track> &tracks, audio_io_handle_t id);
#ifdef DOLBY_DAP_POSTGAIN
    status_t setPostgain(uint32_t max_vol);
#endif
    status_t skipHardBypass();
    std::string getVersion();

private:
    EffectDapController(const sp<AudioFlinger>& audioFlinger);
    EffectDapController(const EffectDapController&);
    EffectDapController& operator=(const EffectDapController&);

    Mutex mLock;
    std::string mVersion;

    static EffectDapController *mInstance;
    // This will allow AudioFlinger to instantiate this class.
    friend class AudioFlinger;

protected:
    status_t setPregainWithStreamType(int maxVol, audio_output_flags_t flags);
    status_t setParam(int32_t paramId, int32_t value);
    status_t setParameters(int32_t paramId, const std::vector<int32_t>& values);
    status_t updateBypassState();
    bool bypassTrack(PlaybackThread::Track* const &track);

    const sp<AudioFlinger> mAudioFlinger;
    sp<EffectModule> mEffect;
    bool mBypassed;
    uint32_t mDapVol;
    uint32_t mMixerVol;
    uint32_t mDirectVol;
    uint32_t mOffloadVol;
    int mAudioFlags;
    uint32_t mMaxMixerVol;
    uint32_t mMaxDirectVol;
    uint32_t mMaxOffloadVol;


    const bool mIsSoundTypesBypassEnabled;
};

#endif//DOLBY_EFFECT_DAP_CONTROLLER_H_
