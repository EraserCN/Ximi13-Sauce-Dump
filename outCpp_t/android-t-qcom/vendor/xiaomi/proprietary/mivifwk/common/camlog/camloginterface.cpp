////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020-2021 Xiaomi Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Xiaomi Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  camlogfetch.cpp
/// @brief General OS specific utility class implementation for Linux
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "camloginterface.h"

#include "log/log.h"

char *getVersion()
{
    return "camlog 1.0";
}

int sendMessageToMqs(char *buf, bool isForceSIGABRT)
{
    return camlog::send_message_to_mqs(buf, isForceSIGABRT);
}

CamlogInterface CAMLOG_INTERFACE = {getVersion, sendMessageToMqs};

void *camlogOpenLib(void)
{
    return &CAMLOG_INTERFACE;
}
