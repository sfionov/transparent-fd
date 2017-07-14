package com.adguard.filter.proxy.transparent;

import android.content.res.AssetManager;
import android.os.Build;
import android.os.Bundle;
import android.os.ParcelFileDescriptor;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;

import org.apache.commons.io.IOUtils;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainActivity extends AppCompatActivity {

    public static final int LISTEN_PORT = 12345;
    private ExecutorService executor = Executors.newSingleThreadExecutor();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        System.loadLibrary("native-lib");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });

        executor.submit(new Runnable() {
            @Override
            public void run() {
                try {
                    MainActivity.this.setupTransparentSocket();
                } catch (Throwable e) {
                    e.printStackTrace();
                }
            }
        });
    }

    private void setupTransparentSocket() throws IOException, InterruptedException {
        String progName;
        if (Build.VERSION.SDK_INT == 15) {
            progName = "create_transparent_socket_sdk15";
        } else {
            progName = "create_transparent_socket_sdk16pie";
        }

        ServerSocketChannel ch = ServerSocketChannel.open();
        File progFile = unpackCreateTransparentSocketProg(progName);
        new File(getApplicationContext().getCacheDir() + "/test-local").delete();
        ParcelFileDescriptor fd = TransparentUtils.bindLocalSocket(getApplicationContext().getCacheDir() + "/test-local");
        Process rootShell = startRootShell();
        executeRootCommand(rootShell, "chmod 0755 " + progFile.getAbsolutePath());
        executeRootCommand(rootShell, progFile.getAbsolutePath() + " " + getApplicationContext().getCacheDir() + "/test-local");
        System.err.println("Receiving file descriptor");
        TransparentUtils.receiveFileDescriptor(ch, fd);
        System.err.println("Received file descriptor");
        executeRootCommand(rootShell, "ip -6 route add local default dev lo table 0xad");
        executeRootCommand(rootShell, "ip -6 rule add from all fwmark 0xad table 0xad");
        executeRootCommand(rootShell, "ip6tables -t mangle -A OUTPUT -p tcp -m owner --uid-owner " + getUid() + " -j RETURN");
        executeRootCommand(rootShell, "ip6tables -t mangle -A OUTPUT -p tcp -j MARK --set-mark 0xad");
        executeRootCommand(rootShell, "ip6tables -t mangle -A PREROUTING -p tcp -m socket -j RETURN");
        executeRootCommand(rootShell, "ip6tables -t mangle -A PREROUTING -p tcp -i lo -s ::1 -j RETURN");
        executeRootCommand(rootShell, "ip6tables -t mangle -A PREROUTING -p tcp -j TPROXY --on-port " + LISTEN_PORT);
        stopRootShell(rootShell);

        ch.socket().bind(new InetSocketAddress(LISTEN_PORT));
        System.err.println("Listening on " + ch.socket().getLocalSocketAddress());
        while (true) {
            SocketChannel accepted = ch.accept();
            System.err.println("Accepted " + accepted.socket().getRemoteSocketAddress() + " -> " + accepted.socket().getLocalSocketAddress());
            accepted.write(ByteBuffer.wrap("HTTP/1.0 400 Bad request\r\n\r\n".getBytes()));
            accepted.close();
        }
    }

    private int getUid() {
        return getApplicationInfo().uid;
    }

    private void executeRootCommand(Process rootShell, String command) throws IOException {
        IOUtils.write(command + "\n", rootShell.getOutputStream());
        try {
            rootShell.getOutputStream().flush();
        } catch (IOException ignored) {}
    }

    private void stopRootShell(Process rootShell) throws IOException {
        executeRootCommand(rootShell, "exit");
        try {
            int status = rootShell.waitFor();
            System.err.println("Root shell exited with status " + status);
            IOUtils.copy(rootShell.getInputStream(), System.err);
            IOUtils.copy(rootShell.getErrorStream(), System.err);
        } catch (InterruptedException ignored) {}
    }

    private Process startRootShell() throws IOException {
        return Runtime.getRuntime().exec("su");
    }

    private File unpackCreateTransparentSocketProg(String progName) throws IOException {
        AssetManager assetManager = getAssets();
        InputStream is = null;
        OutputStream os = null;
        File progFile = new File(getCacheDir(), progName);
        try {
            is = assetManager.open(progName);
            os = new FileOutputStream(progFile);
            IOUtils.copyLarge(is, os);
        } finally {
            IOUtils.closeQuietly(is);
            IOUtils.closeQuietly(os);
        }
        return progFile;
    }
}
