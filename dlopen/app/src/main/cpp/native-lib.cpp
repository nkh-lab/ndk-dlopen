#include <android/log.h>
#include <boost/dll/import.hpp>
#include <boost/function.hpp>
#include <dlfcn.h>
#include <jni.h>
#include <string>

namespace {
const char* TAG = __FILE_NAME__;

void test_dlopen(const std::string& lib);
void test_boost_dll_import_alias(const std::string& lib);
void test_dlopen_system_lib();
} // namespace

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__))

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_dlopen_MainActivity_stringFromJNI(JNIEnv* env, jobject /* this */, jstring path)
{
    std::string hello = "Hello from C++";
    jboolean isCopy;

    std::string lib =
        std::string{env->GetStringUTFChars(path, nullptr)} +
        "/libplugin.so"; // works if AndroidManifest.xml: application.android:extractNativeLibs="true"
    // std::string lib = "libplugin.so"; // always works

    test_dlopen(lib);
    test_boost_dll_import_alias(lib);
    test_dlopen_system_lib();

    return env->NewStringUTF(hello.c_str());
}

namespace {
void test_dlopen(const std::string& lib)
{
    void* handle = dlopen(lib.c_str(), RTLD_LAZY);

    using pcount_t = int (*)();

    if (handle)
    {
        LOGI("dlopen(%s): OK", lib.c_str());

        auto pcount_c = (pcount_t)dlsym(handle, "count");

        if (pcount_c != nullptr)
        {
            for (int i = 0; i < 3; ++i) LOGI("pcount_c(): %d", pcount_c());
        }
        else
            LOGW("pcount_c = nulptr");

        auto pcount_cpp = (pcount_t)dlsym(handle, "_ZN2my5countEv");

        if (pcount_cpp != nullptr)
        {
            for (int i = 0; i < 3; ++i) LOGI("pcount_cpp(): %d", pcount_cpp());
        }
        else
            LOGW("pcount_cpp = nulptr");

        pcount_t* pcount_alias = (pcount_t*)(dlsym(handle, "alias_count"));

        if (pcount_alias != nullptr && *pcount_alias != nullptr)
        {
            for (int i = 0; i < 3; ++i) LOGI("(*pcount_alias)(): %d", (*pcount_alias)());
        }
        else
            LOGW("pcount_alias = nulptr");

        dlclose(handle);
    }
    else
        LOGW("dlopen(%s): NOK", lib.c_str());
}

void test_boost_dll_import_alias(const std::string& lib)
{
    boost::function<int()> boost_alias_count =
        boost::dll::import_alias<int()>(lib, "boost_alias_count");

    if (boost_alias_count)
    {
        for (int i = 0; i < 3; ++i) LOGI("boost_alias_count(): %d", boost_alias_count());
    }
    else
        LOGW("boost_alias_count = false");
}

void test_dlopen_system_lib()
{
    void* handle = dlopen("libaudioflinger.so", RTLD_LAZY | RTLD_GLOBAL);

    if (handle)
    {
        LOGW("dlopen(%s): OK", "libaudioflinger.so");
    }
    else
        LOGW("dlopen(%s): NOK", "libaudioflinger.so");
}
} // namespace
