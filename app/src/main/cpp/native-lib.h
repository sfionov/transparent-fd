//
// Created by s.fionov on 13.07.17.
//

#ifndef TRANSPARENT_FD_NATIVE_LIB_H
#define TRANSPARENT_FD_NATIVE_LIB_H

#include <jni.h>

extern "C" {

JNIEXPORT void JNICALL Java_com_adguard_filter_proxy_transparent_TransparentUtils_makeSocketTransparent
(JNIEnv *env, jclass type, jobject socketChannel, jstring socketPath);

JNIEXPORT jboolean JNICALL
        Java_com_adguard_filter_proxy_transparent_TransparentUtils_isSocketTransparent(JNIEnv *env, jclass type,
jobject socketChannel);

JNIEXPORT jint JNICALL
        Java_com_adguard_filter_proxy_transparent_TransparentUtils_bindLocalSocket0(JNIEnv *env, jclass type,
jstring socketPath_);

JNIEXPORT void JNICALL
Java_com_adguard_filter_proxy_transparent_TransparentUtils_receiveFileDescriptor0(JNIEnv *env, jclass type,
                                                                                  jobject socketChannel,
                                                                                  jint fd);
}

#endif //TRANSPARENT_FD_NATIVE_LIB_H
