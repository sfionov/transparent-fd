package com.adguard.filter.proxy.transparent;

import android.os.ParcelFileDescriptor;

import java.io.IOException;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.spi.AbstractSelectableChannel;

/**
 * Created by s.fionov on 13.07.17.
 */

public class TransparentUtils {
    public static native void makeSocketTransparent(AbstractSelectableChannel socketChannel, String socketPath) throws IOException;

    public static native boolean isSocketTransparent(AbstractSelectableChannel socketChannel) throws IOException;

    private static native int bindLocalSocket0(String socketPath) throws IOException;

    public static ParcelFileDescriptor bindLocalSocket(String socketPath) throws IOException {
        return ParcelFileDescriptor.adoptFd(bindLocalSocket0(socketPath));
    }

    private static native void receiveFileDescriptor0(AbstractSelectableChannel ch, int fd);

    public static void receiveFileDescriptor(AbstractSelectableChannel ch, ParcelFileDescriptor fd) {
        receiveFileDescriptor0(ch, fd.getFd());
    }
}
