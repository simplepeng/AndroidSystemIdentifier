#include <jni.h>
#include <string>
#include <sys/stat.h>

static jstring getUpdate(JNIEnv *env, jclass) {
    struct stat sb;
    int updates = 0,updatens = 0;
    if (stat("/data/data", &sb) == -1) {
        //获取失败
    } else {
        updatens = (int) sb.st_atim.tv_nsec;
        updates = (int) sb.st_atim.tv_sec;
    }
    std::string idRes = std::to_string(updates) + "." + std::to_string(updatens);
    return env->NewStringUTF(idRes.c_str());
}

static jstring getBoot(JNIEnv *env, jclass) {
    FILE *fp = fopen("/proc/sys/kernel/random/boot_id", "r");
    char boot[37];
    if (fp == NULL)
        //"Error opening file"
        boot[0]= '\0';
    else {
        fgets(boot,37,fp);
        fclose(fp);
    }
    std::string sboot = boot;
    return env->NewStringUTF(sboot.c_str());
}

static const char *classPathName = "simple/android/asi/SystemIdentifier";

static const JNINativeMethod gMethods[] = {
        {"getUpdateMark", "()Ljava/lang/String;", (void *) getUpdate},
        {"getBootMark", "()Ljava/lang/String;", (void *) getBoot}
};

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    if((vm->GetEnv((void **) &env, JNI_VERSION_1_4)) != JNI_OK ){
        return JNI_FALSE;
    }
    jclass clazz = env->FindClass(classPathName);
    if(clazz == NULL){
        return JNI_FALSE;
    }
    if((env->RegisterNatives(clazz, gMethods, 2) < 0)){
        return JNI_FALSE;
    }
    return JNI_VERSION_1_4;
}