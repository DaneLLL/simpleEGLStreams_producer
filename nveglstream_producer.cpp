/**
 * Copyright (c) 2017, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include "nveglstream_producer.h"
#include "eglstrm_common.h"

#include <GLES3/gl31.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

pthread_t g_thread_id;

static void *
thread_start(void *arg)
{
    int ret = 0, j = 0;
    EGLint streamState = 0;
    float r = 0;
    float g = 0.5;
    float b = 1;

    printf("Thread created\n");
    usleep(500000);

    EGLStreamCreateProducer();

    glClearColor( r, g, b, 1 ); // blue-ish background
    glClear( GL_COLOR_BUFFER_BIT );
    eglSwapBuffers_wrapper();
    usleep(16000);

    int frame = 0;

    while (frame < 100) {
        if (frame % 15 == 0) {
            r = (r > 0)?0:0.5;
            g = (g > 0)?0:0.5;
            b = (b > 0.5)?0.5:1;
        }
	    glClearColor( r, g, b, 1 ); // blue-ish background
        glClear( GL_COLOR_BUFFER_BIT );
        eglSwapBuffers_wrapper();

        usleep(32000);
        frame ++;
    }

    return 0;
}

extern "C" int
start_eglstream_producer (int producer_index, EGLDisplay * display,
    EGLStreamKHR * stream, int width, int height)
{
    int ret = 0;

    printf ("NVEGLStreamProducer: %s ++\n", __func__);

    switch (producer_index)
    {
    case EGLSTREAM_PRODUCER_ID_CUSTOM:
      if(!eglSetupExtensions()) {
        printf("SetupExtentions failed \n");
        goto done;
      }

      if(!EGLStreamInit()) {
        printf("EGLStream Init failed.\n");
        goto done;
      }

      ret = pthread_create (&g_thread_id, NULL, thread_start, NULL);

      * display = g_display;
      * stream = eglStream;
      break;
    default:
      printf ("NVEGLStream_Producer:%s Invalid EGLStream Producer Index = %d\n",
          __func__, producer_index);
      ret = -1;
    }

    printf ("NVEGLStreamProducer: %s --\n", __func__);
    return ret;
done:
    return -1;
}

extern "C" int
stop_eglstream_producer (int producer_index)
{
  int ret = 0;
  EGLint streamState = 0;

  printf ("NVEGLStreamProducer: %s ++\n", __func__);
  switch (producer_index)
  {
    case EGLSTREAM_PRODUCER_ID_CUSTOM:
    pthread_join(g_thread_id, NULL);


    printf("Producer Disconnected \n");
    if(!eglQueryStreamKHR_wrapper(
                g_display,
                eglStream,
                EGL_STREAM_STATE_KHR,
                &streamState)) {
        printf("Cuda consumer, eglQueryStreamKHR EGL_STREAM_STATE_KHR failed\n");
    }
    if(streamState != EGL_STREAM_STATE_DISCONNECTED_KHR) {
        EGLStreamFini();
    }
      break;
    default:
      printf ("NVEGLStream_Producer:%s Invalid EGLStream Producer Index = %d\n",
          __func__, producer_index);
      ret = -1;
      break;
  }

  printf ("NVEGLStreamProducer: %s --\n", __func__);
  return ret;
done:
  return -1;
}

