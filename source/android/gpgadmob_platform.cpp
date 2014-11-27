/*
 * android-specific implementation of the gpgadmob extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "gpgadmob_internal.h"

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"

static jobject g_Obj;
static jmethodID g_AdmobInit;
static jmethodID g_AdmobTestDevice;
static jmethodID g_AdmobResize;
static jmethodID g_AdmobShow;
static jmethodID g_AdmobRefresh;
static jmethodID g_AdmobHide;
static jmethodID g_AdmobMove;
static jmethodID g_AdmobInterestialPreload;
static jmethodID g_AdmobInterestialIsReady;
static jmethodID g_AdmobInterestialIsShown;
static jmethodID g_AdmobInterestialWasShown;
static jmethodID g_AdmobInterestialHasBeenUsed;
static jmethodID g_AdmobInterestialShow;
static jmethodID g_AdmobInterestialHide;
static jmethodID g_AdmobBannerIsClicked;
static jmethodID g_AdmobInterestialIsClicked;

s3eResult gpgadmobInit_platform()
{
    // Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;

    // Get the extension class
    jclass cls = s3eEdkAndroidFindClass("gpgadmob");
    if (!cls)
        goto fail;

    // Get its constructor
    cons = env->GetMethodID(cls, "<init>", "()V");
    if (!cons)
        goto fail;

    // Construct the java class
    obj = env->NewObject(cls, cons);
    if (!obj)
        goto fail;

    // Get all the extension methods
    g_AdmobInit = env->GetMethodID(cls, "AdmobInit", "(Ljava/lang/String;III)I");
    if (!g_AdmobInit)
        goto fail;

    g_AdmobTestDevice = env->GetMethodID(cls, "AdmobTestDevice", "(Ljava/lang/String;)I");
    if (!g_AdmobTestDevice)
        goto fail;

    g_AdmobResize = env->GetMethodID(cls, "AdmobResize", "(I)I");
    if (!g_AdmobResize)
        goto fail;

    g_AdmobShow = env->GetMethodID(cls, "AdmobShow", "()I");
    if (!g_AdmobShow)
        goto fail;

    g_AdmobRefresh = env->GetMethodID(cls, "AdmobRefresh", "()I");
    if (!g_AdmobRefresh)
        goto fail;

    g_AdmobHide = env->GetMethodID(cls, "AdmobHide", "()I");
    if (!g_AdmobHide)
        goto fail;

    g_AdmobMove = env->GetMethodID(cls, "AdmobMove", "(III)I");
    if (!g_AdmobMove)
        goto fail;

    g_AdmobInterestialPreload = env->GetMethodID(cls, "AdmobInterestialPreload", "(Ljava/lang/String;)I");
    if (!g_AdmobInterestialPreload)
        goto fail;

    g_AdmobInterestialIsReady = env->GetMethodID(cls, "AdmobInterestialIsReady", "()Z");
    if (!g_AdmobInterestialIsReady)
        goto fail;

    g_AdmobInterestialIsShown = env->GetMethodID(cls, "AdmobInterestialIsShown", "()Z");
    if (!g_AdmobInterestialIsShown)
        goto fail;

    g_AdmobInterestialWasShown = env->GetMethodID(cls, "AdmobInterestialWasShown", "()Z");
    if (!g_AdmobInterestialWasShown)
        goto fail;

    g_AdmobInterestialHasBeenUsed = env->GetMethodID(cls, "AdmobInterestialHasBeenUsed", "()Z");
    if (!g_AdmobInterestialHasBeenUsed)
        goto fail;

    g_AdmobInterestialShow = env->GetMethodID(cls, "AdmobInterestialShow", "()I");
    if (!g_AdmobInterestialShow)
        goto fail;

    g_AdmobInterestialHide = env->GetMethodID(cls, "AdmobInterestialHide", "()I");
    if (!g_AdmobInterestialHide)
        goto fail;

    g_AdmobBannerIsClicked = env->GetMethodID(cls, "AdmobBannerIsClicked", "()Z");
    if (!g_AdmobBannerIsClicked)
        goto fail;

    g_AdmobInterestialIsClicked = env->GetMethodID(cls, "AdmobInterestialIsClicked", "()Z");
    if (!g_AdmobInterestialIsClicked)
        goto fail;



    IwTrace(GPGADMOB, ("GPGADMOB init success"));
    g_Obj = env->NewGlobalRef(obj);
    env->DeleteLocalRef(obj);
    env->DeleteGlobalRef(cls);

    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;

fail:
    jthrowable exc = env->ExceptionOccurred();
    if (exc)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
        IwTrace(gpgadmob, ("One or more java methods could not be found"));
    }

    env->DeleteLocalRef(obj);
    env->DeleteGlobalRef(cls);
    return S3E_RESULT_ERROR;

}

void gpgadmobTerminate_platform()
{ 
    // Add any platform-specific termination code here
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->DeleteGlobalRef(g_Obj);
    g_Obj = NULL;
}

s3eResult AdmobInit_platform(const char* adUnitId, int adType, int x, int y)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring adUnitId_jstr = env->NewStringUTF(adUnitId);
    return (s3eResult)env->CallIntMethod(g_Obj, g_AdmobInit, adUnitId_jstr, adType, x, y);
}

s3eResult AdmobTestDevice_platform(const char* szTestDeviceID)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring szTestDeviceID_jstr = env->NewStringUTF(szTestDeviceID);
    return (s3eResult)env->CallIntMethod(g_Obj, g_AdmobTestDevice, szTestDeviceID_jstr);
}

s3eResult AdmobResize_platform(int ad_type)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eResult)env->CallIntMethod(g_Obj, g_AdmobResize, ad_type);
}

s3eResult AdmobShow_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eResult)env->CallIntMethod(g_Obj, g_AdmobShow);
}

s3eResult AdmobRefresh_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eResult)env->CallIntMethod(g_Obj, g_AdmobRefresh);
}

s3eResult AdmobHide_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eResult)env->CallIntMethod(g_Obj, g_AdmobHide);
}

s3eResult AdmobMove_platform(int orientation, int x, int y)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eResult)env->CallIntMethod(g_Obj, g_AdmobMove, orientation, x, y);
}

s3eResult AdmobInterestialPreload_platform(const char * adUnitId)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring adUnitId_jstr = env->NewStringUTF(adUnitId);
    return (s3eResult)env->CallIntMethod(g_Obj, g_AdmobInterestialPreload, adUnitId_jstr);
}

bool AdmobInterestialIsReady_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_AdmobInterestialIsReady);
}

bool AdmobInterestialIsShown_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_AdmobInterestialIsShown);
}

bool AdmobInterestialWasShown_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_AdmobInterestialWasShown);
}

bool AdmobInterestialHasBeenUsed_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_AdmobInterestialHasBeenUsed);
}

s3eResult AdmobInterestialShow_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eResult)env->CallIntMethod(g_Obj, g_AdmobInterestialShow);
}

s3eResult AdmobInterestialHide_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eResult)env->CallIntMethod(g_Obj, g_AdmobInterestialHide);
}

bool AdmobBannerIsClicked_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_AdmobBannerIsClicked);
}

bool AdmobInterestialIsClicked_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_AdmobInterestialIsClicked);
}
