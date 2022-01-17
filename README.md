# ndk-dlopen
Android Studio example project for testing native libraries dynamic loading by using:
- dlopen()/dlsym()/dlclose()
- boost::dll::import_alias()

## Environment
- Android Studio
- CMake 3.12 (for boost-cmake)

## Dependencies
Git submodule projects:
- boost-cmake: Used CMake adapted boost (https://github.com/Orphis/boost-cmake).

## Project setup
1. Clone main git project:
```
git clone https://github.com/nkh-lab/ndk-dlopen.git
```
2. Clone submodule projects:
```
git submodule update --init
```

## Build and run
1. Open project in Android Studio
2. Build and run on emulator 
3. Expected application output in `logcat`:
```
2022-01-17 16:43:58.548 8779-8779/com.example.dlopen I/native-lib.cpp: dlopen(/data/app/~~n2LWrvrFpbL8tiBLY82sVg==/com.example.dlopen-MRIG2JQE0v9GAY3DxRNsTA==/lib/x86/libplugin.so): OK
2022-01-17 16:43:58.548 8779-8779/com.example.dlopen I/native-lib.cpp: pcount_c(): 1
2022-01-17 16:43:58.548 8779-8779/com.example.dlopen I/native-lib.cpp: pcount_c(): 2
2022-01-17 16:43:58.548 8779-8779/com.example.dlopen I/native-lib.cpp: pcount_c(): 3
2022-01-17 16:43:58.548 8779-8779/com.example.dlopen I/native-lib.cpp: pcount_cpp(): 1
2022-01-17 16:43:58.548 8779-8779/com.example.dlopen I/native-lib.cpp: pcount_cpp(): 2
2022-01-17 16:43:58.548 8779-8779/com.example.dlopen I/native-lib.cpp: pcount_cpp(): 3
2022-01-17 16:43:58.548 8779-8779/com.example.dlopen I/native-lib.cpp: (*pcount_alias)(): 4
2022-01-17 16:43:58.548 8779-8779/com.example.dlopen I/native-lib.cpp: (*pcount_alias)(): 5
2022-01-17 16:43:58.548 8779-8779/com.example.dlopen I/native-lib.cpp: (*pcount_alias)(): 6
2022-01-17 16:43:58.549 8779-8779/com.example.dlopen I/native-lib.cpp: boost_alias_count(): 1
2022-01-17 16:43:58.549 8779-8779/com.example.dlopen I/native-lib.cpp: boost_alias_count(): 2
2022-01-17 16:43:58.549 8779-8779/com.example.dlopen I/native-lib.cpp: boost_alias_count(): 3
2022-01-17 16:43:58.549 8779-8779/com.example.dlopen W/native-lib.cpp: dlopen(libaudioflinger.so): NOK
```


