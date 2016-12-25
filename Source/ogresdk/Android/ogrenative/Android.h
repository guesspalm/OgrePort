#ifndef OGRE_ANDROID_H
#define OGRE_ANDROID_H

#include "NativeActivity.h"
// #include "IAndroidHandler.h"
// #include "NotificationManager.h"
// 
// namespace OgreNative
// {
//     void PollEvents();
//     void SetEventCallback( MessageCallbackFunction pCallback );
//     void SetEventHandler( IAndroidHandler* pHandler );

//     ANativeWindow* GetWindow();
//     AAssetManager* GetAssetManager();
//     bool IsWindowVisible();

//     void ShowKeyboard();
//     void HideKeyboard();

//     const char* GetAppDir();

//     JNIEnv* GetJNIEnv();
//     jobject GetJNIActivity();

//     ClassLoader& GetClassLoader();
//     NotificationManager& GetNotificationManager();

//     NativeActivity& GetNativeActivity();
// };

#ifndef _LIB
extern "C"
{
    void init_native_activity( JNIEnv* pEnv, jobject pObj, NativeActivity** pInterface );

    void uninit_native_activity( JNIEnv* pEnv, jobject pObj, NativeActivity** pInterface );
}

#endif

#endif