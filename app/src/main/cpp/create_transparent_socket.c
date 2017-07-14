//
// Created by s.fionov on 12.07.17.
//


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/stat.h>

int setsockcreatecon(const char *context) {
    int fd = open("/proc/self/attr/sockcreate", O_RDWR);
    if (fd == -1) {
        return -1;
    }
    int w = (int) write(fd, context, strlen(context));
    close(fd);
    return w;
}

#undef IP_TRANSPARENT
#define IP_TRANSPARENT 19
#undef IPV6_V6ONLY
#define IPV6_V6ONLY 26

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Please provide file name for unix socket on command line\n");
        exit(1);
    }

    char name[PATH_MAX];
    realpath(argv[1], name);

    struct sockaddr_un sun;
    sun.sun_family = AF_UNIX;
    strncpy(sun.sun_path, name, sizeof(sun.sun_path));
    int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (fd == -1) {
        fprintf(stderr, "Error creating unix domain socket: %s\n", strerror(errno));
        exit(1);
    }
    // Set socket context same as all ordinary apps context. No-op on Android 4.x
    setsockcreatecon("u:r:untrusted_app:s0");
    int server_fd = socket(AF_INET6, SOCK_STREAM, 0);
    if (server_fd == -1) {
        fprintf(stderr, "Error creating tcp socket: %s\n", strerror(errno));
        exit(1);
    }
    int value = 0;
    if (setsockopt(server_fd, SOL_IPV6, IPV6_V6ONLY, &value, sizeof(int)) == -1) {
        fprintf(stderr, "Error making socket dual-stack: %s\n", strerror(errno));
        exit(1);
    }
    value = 1;
    if (setsockopt(server_fd, SOL_IP, IP_TRANSPARENT, &value, sizeof(int)) == -1) {
        fprintf(stderr, "Error making socket transparent: %s\n", strerror(errno));
        exit(1);
    }

    struct cmsghdr *cmsg = calloc(1, CMSG_LEN(sizeof(int)));
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(int));
    *(int *)CMSG_DATA(cmsg) = server_fd;
    struct msghdr msg = {
            .msg_name = &sun,
            .msg_namelen = sizeof(sun),
            .msg_iov = NULL,
            .msg_iovlen = 0,
            .msg_control = cmsg,
            .msg_controllen = cmsg->cmsg_len
    };

    if (sendmsg(fd, &msg, 0) == -1) {
        fprintf(stderr, "Error sending message to socket: %s\n", strerror(errno));
        exit(1);
    }

    return 0;
}
