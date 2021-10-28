#include <jni.h>
#include <iostream>
#include <android/log.h>

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "jni_log", __VA_ARGS__)

//定义一个全局 java vm 实例
JavaVM *jvm;
//在加载动态库时回去调用 JNI_Onload 方法，在这里可以得到 JavaVM 实例对象
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGD("JNI_OnLoad");
    JNIEnv *env;
    jvm = vm;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    return JNI_VERSION_1_6;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_xmly_learnjni_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */,jstring name) {
    jboolean isCopy = JNI_TRUE;
    const char *ca = env->GetStringUTFChars(name,&isCopy);
    std::string result = "参数：";
    result.append(ca);
    env->ReleaseStringUTFChars(name,ca);
    return env->NewStringUTF(result.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_xmly_learnjni_MainActivity_stringFromJNI2(
        JNIEnv* env,jobject thiz) {
    jclass clazz = env->GetObjectClass(thiz);
    jmethodID mid = env->GetMethodID(clazz,"returnFromJNI","()V");
    jvm->AttachCurrentThread(&env, nullptr)
    env->CallVoidMethod(thiz,mid);
    jvm->DetachCurrentThread()
    std::string hello = "Hello from C++!!!2333";
    return env->NewStringUTF(hello.c_str());
}