#include "common/OgreBaseApp.h"
#include "utils/ReflexCpp.h"
#include "utils/Any.h"

#include "OgreAndroidEGLWindow.h"
#include "OgreAPKFileSystemArchive.h"
#include "OgreAPKZipArchive.h"

LOGGER_IMPLEMENT(OgreBaseApp);

static Ogre::DataStreamPtr openAPKFile(AAssetManager* assetManager, const Ogre::String& fileName) {
     Ogre::DataStreamPtr stream;
     
     AAsset* asset = AAssetManager_open(assetManager, fileName.c_str(), AASSET_MODE_BUFFER);
     if(asset) {
         off_t length = AAsset_getLength(asset);
         void* membuf = OGRE_MALLOC(length, Ogre::MEMCATEGORY_GENERAL);
         memcpy(membuf, AAsset_getBuffer(asset), length);
         AAsset_close(asset);

         stream = Ogre::DataStreamPtr(new Ogre::MemoryDataStream(membuf, length, true, true));
     }
     return stream;
}

void OgreBaseApp::loadResources(const char *name) {

    cf.load(openAPKFile(mAppInterface->GetAssetManager(), name));

    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
     while (seci.hasMoreElements()) {
         Ogre::String sec, type, arch;
         sec = seci.peekNextKey();
         Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
         Ogre::ConfigFile::SettingsMultiMap::iterator i;

         for (i = settings->begin(); i != settings->end(); i++) {
             type = i->first;
             arch = i->second;
             Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
         }
     }
}

// Surface
void OgreBaseApp::OnSurfaceCreated() {
    InitGameWindow();
}

void OgreBaseApp::OnSurfaceChanged(int iPixelFormat, int iWidth, int iHeight) {
    InitGameScene();
}

void OgreBaseApp::OnSurfaceDestroyed() {
   if(mRoot && mRenderWindow)
       static_cast<Ogre::AndroidEGLWindow*>(mRenderWindow)->_destroyInternalResources();
}

void OgreBaseApp::InitGameWindow() {
    AConfiguration* config = AConfiguration_new();
//    AConfiguration_fromAssetManager(config, mAppInterface->GetAssetManager());
//    AConfiguration_setOrientation(config, 2);

    if(!mRenderWindow) {
        Ogre::APKFileSystemArchiveFactory* apkFileSystem = new Ogre::APKFileSystemArchiveFactory(mAppInterface->GetAssetManager());
        Ogre::APKZipArchiveFactory* apkZip = new Ogre::APKZipArchiveFactory(mAppInterface->GetAssetManager());

        Ogre::ArchiveManager::getSingleton().addArchiveFactory( apkFileSystem );
        Ogre::ArchiveManager::getSingleton().addArchiveFactory( apkZip );

        Ogre::NameValuePairList opt;
        opt["externalWindowHandle"] = Ogre::StringConverter::toString((int)mAppInterface->GetWindow());
        // opt["androidConfig"] = Ogre::StringConverter::toString((int)config);

        mRenderWindow = mRoot->createRenderWindow("OgreWindow", 1920, 1080, true, &opt);

        Ogre::WindowEventUtilities::addWindowEventListener(mRenderWindow, this);

        InitStartScene();
    } else {
        static_cast<Ogre::AndroidEGLWindow*>(mRenderWindow)->_createInternalResources(mAppInterface->GetWindow(), NULL);
    }
    AConfiguration_delete(config);
}

void OgreApplicationMain(const char* appName, IAppInterface* appInterface) {
    Any appInstance = CreateObject(appName);
    OgreBaseApp* baseApp = any_cast<OgreBaseApp*>(appInstance);
    baseApp->go(appInterface);
    delete baseApp;
}