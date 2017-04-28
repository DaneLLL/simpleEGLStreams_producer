/**
 * Copyright (c) 2017, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#ifndef _NVEGLSTREAM_PRODUCER_H_
#define _NVEGLSTREAM_PRODUCER_H_

#include <EGL/egl.h>
#include <EGL/eglext.h>
//#include <eglapiinterface.h>

extern EGLDisplay g_display;
extern EGLStreamKHR eglStream;

typedef enum
{
  EGLSTREAM_PRODUCER_ID_CUSTOM = 0,
  EGLSTREAM_PRODUCER_ID_MAX,
} EGLStream_Producer_ID;
extern "C" int
start_eglstream_producer (int producer_index, EGLDisplay * display,
    EGLStreamKHR * stream, int width, int height);

extern "C" int
stop_eglstream_producer (int producer_index);

#endif
