package com.example.dlopen;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    static final String TAG = "MainActivity";

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);

        String libDir = new File(getPackageCodePath()).getParent() + "/lib/" + convertABItoLibDir(Build.SUPPORTED_ABIS[0]);
        Log.d(TAG, "libDir: " + libDir);

        tv.setText(stringFromJNI(libDir));
    }

    private String convertABItoLibDir(String abi) {
        String ret = abi;

        if (abi.equals( "arm64-v8a")) {
            ret = "arm64";
        }

        return ret;
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI(String path);
}