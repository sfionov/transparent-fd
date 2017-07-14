#include "native-lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>


int sendFdViaUnixSocket(int fd, const char *unix_socket_path, char error_msg[256], size_t error_msg_len) {
    struct sockaddr_un sun;
    sun.sun_family = AF_UNIX;
    strncpy(sun.sun_path, unix_socket_path, sizeof(sun.sun_path));
    int unix_socket_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (unix_socket_fd == -1) {
        return -1;
    }

    connect(unix_socket_fd, (const struct sockaddr *) &sun, sizeof(sun));

    struct cmsghdr *cmsg = (cmsghdr *) calloc(1, CMSG_LEN(sizeof(int)));
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(int));
    *(int*)CMSG_DATA(cmsg) = fd;

    struct msghdr msg = {
            .msg_name = &sun,
            .msg_namelen = sizeof(sun),
            .msg_iov = NULL,
            .msg_iovlen = 0,
            .msg_control = cmsg,
            .msg_controllen = CMSG_LEN(sizeof(int))
    };

    int ret = (int) sendmsg(unix_socket_fd, &msg, 0);
    if (ret == -1) {
        snprintf(error_msg, error_msg_len,
                 "Can't send command to make socket transparent to unix socket: %s", strerror(errno));
    }

    close(unix_socket_fd);
    free(cmsg);
    return ret;
}

static int getFd(JNIEnv *env, jobject socketChannel) {

    jclass fdChannelClass = env->FindClass("java/nio/FileDescriptorChannel");
    if (fdChannelClass == nullptr) {
        env->ExceptionClear();
        fdChannelClass = env->FindClass("sun/nio/ch/SelChImpl");
        if (fdChannelClass == nullptr) {
            return -1;
        }
    }
    jmethodID method = env->GetMethodID(fdChannelClass, "getFD", "()Ljava/io/FileDescriptor;");
    if (method == nullptr) {
        return -1;
    }
    jobject fileDescriptor = env->CallObjectMethod(socketChannel, method);
    if (fileDescriptor == nullptr) {
        if (jclass exc = env->FindClass("java/io/IOException")) {
            env->ThrowNew(exc, "Can't get FileDescriptor object of SocketChannel");
        }
        // If class is not found, exception already set
        return -1;
    }
    jclass fileDescriptorClass = env->FindClass("java/io/FileDescriptor");
    if (fileDescriptorClass == nullptr) {
        env->DeleteLocalRef(fileDescriptor);
        return -1;
    }

    jfieldID field = env->GetFieldID(fileDescriptorClass, "descriptor", "I");
    if (field == nullptr) {
        env->ExceptionClear();
        field = env->GetFieldID(fileDescriptorClass, "fd", "I");
        if (field == nullptr) {
            env->DeleteLocalRef(fileDescriptor);
            return -1;
        }
    }

    int fd = env->GetIntField(fileDescriptor, field);
    env->DeleteLocalRef(fileDescriptor);

    return fd;
}

void
Java_com_adguard_filter_proxy_transparent_TransparentUtils_makeSocketTransparent(JNIEnv *env, jclass type,
                                                                                 jobject socketChannel,
                                                                                 jstring socketPath) {
    int fd = getFd(env, socketChannel);
    if (fd == -1) {
        if (jclass exc = env->FindClass("java/io/IOException")) {
            env->ThrowNew(exc, "Can't get file descriptor from socket channel");
        }
        return;
    }

    jboolean socketPathCharsIsCopy;
    const char *socketPathChars = env->GetStringUTFChars(socketPath, &socketPathCharsIsCopy);

    char error[256] = "";
    if (sendFdViaUnixSocket(fd, socketPathChars, error, sizeof(error)) == -1) {
        if (jclass exc = env->FindClass("java/io/IOException")) {
            env->ThrowNew(exc, error);
        }
    }

    if (socketPathCharsIsCopy) {
        env->ReleaseStringUTFChars(socketPath, socketPathChars);
    }
}

jboolean
Java_com_adguard_filter_proxy_transparent_TransparentUtils_isSocketTransparent(JNIEnv *env, jclass type,
                                                                               jobject socketChannel) {
    int fd = getFd(env, socketChannel);
    if (fd == -1) {
        if (jclass exc = env->FindClass("java/io/IOException")) {
            env->ThrowNew(exc, "Can't get file descriptor from socket channel");
        }
        return JNI_FALSE;
    }

    int value;
    socklen_t value_len = sizeof(value);
    if (getsockopt(fd, SOL_IP, IP_TRANSPARENT, &value, &value_len) == -1) {
        if (jclass exc = env->FindClass("java/io/IOException")) {
            char error[256];
            snprintf(error, sizeof(error), "Can't get socket option: %s", strerror(errno));
            env->ThrowNew(exc, error);
        }
    }

    return (jboolean) value;
}

jint Java_com_adguard_filter_proxy_transparent_TransparentUtils_bindLocalSocket0(JNIEnv *env, jclass type,
                                                                                jstring socketPath_) {
    const char *socketPath = env->GetStringUTFChars(socketPath_, 0);

    struct sockaddr_un sun;
    sun.sun_family = AF_UNIX;
    strncpy(sun.sun_path, socketPath, sizeof(sun.sun_path));
    int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (fd == -1) {
        char error[256];
        snprintf(error, sizeof(error), "Error creating unix domain socket: %s\n", strerror(errno));
        if (jclass exc = env->FindClass("java/io/IOException")) {
            env->ThrowNew(exc, error);
        }
        return -1;
    }
    if (bind(fd, (const struct sockaddr *) &sun, sizeof(sun)) == -1) {
        char error[256];
        snprintf(error, sizeof(error), "Error binding unix domain socket to file: %s\n", strerror(errno));
        if (jclass exc = env->FindClass("java/io/IOException")) {
            env->ThrowNew(exc, error);
        }
        return -1;
    }

    env->ReleaseStringUTFChars(socketPath_, socketPath);

    return fd;
}

void
Java_com_adguard_filter_proxy_transparent_TransparentUtils_receiveFileDescriptor0(JNIEnv *env, jclass type,
                                                                                  jobject socketChannel,
                                                                                  jint fd) {

    int sock_fd = getFd(env, socketChannel);
    if (sock_fd == -1) {
        if (jclass exc = env->FindClass("java/io/IOException")) {
            env->ThrowNew(exc, "Can't get file descriptor from socket channel");
        }
    }

    struct cmsghdr *cmsg = (cmsghdr *) calloc(1, CMSG_LEN(sizeof(int)));
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(int));
    struct msghdr msg = {
            .msg_control = &cmsg,
            .msg_controllen = cmsg->cmsg_len
    };

    if (recvmsg(fd, &msg, 0) == -1) {
        char error[256];
        snprintf(error, sizeof(error), "Error receiving message on socket: %s\n", strerror(errno));
        if (jclass exc = env->FindClass("java/io/IOException")) {
            env->ThrowNew(exc, error);
        }
        return;
    }

    struct cmsghdr *cmsg_recvd = CMSG_FIRSTHDR(&msg);
    if (!cmsg_recvd || cmsg_recvd->cmsg_len < sizeof(int)) {
        if (jclass exc = env->FindClass("java/io/IOException")) {
            env->ThrowNew(exc, "Control message length is too short");
        }
        return;
    }
    int passed_fd = *(int *) CMSG_DATA(cmsg_recvd);
    int value = 1;
    socklen_t value_len = sizeof(value);
    if (getsockopt(passed_fd, SOL_IP, IP_TRANSPARENT, &value, &value_len) == -1) {
        if (jclass exc = env->FindClass("java/io/IOException")) {
            env->ThrowNew(exc, "Can't get socket option");
        }
        return;
    }

    if (!value) {
        if (jclass exc = env->FindClass("java/io/IOException")) {
            env->ThrowNew(exc, "Received socket is not transparent");
        }
    }

    if (dup2(passed_fd, sock_fd) == -1) {
        if (jclass exc = env->FindClass("java/io/IOException")) {
            env->ThrowNew(exc, "Can't set socketchannels fd to passed fd");
        }
    }

    return;
}
