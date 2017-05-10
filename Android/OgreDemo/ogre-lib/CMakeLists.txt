# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set(CPP_DIR src/main/cpp)

set(OGRESDK_ROOT ${CPP_DIR}/ogresdk)
set(OGREAPP_ROOT ${CPP_DIR}/ogreapp)
set(THIRDPARTY_ROOT thirdparty)
set(ZZIP_ROOT ${THIRDPARTY_ROOT}/Zzip)
set(FREEIMAGE_ROOT ${THIRDPARTY_ROOT}/FreeImage)
set(OGRE_ROOT ${THIRDPARTY_ROOT}/Ogre)
set(FREETYPE_ROOT ${THIRDPARTY_ROOT}/FreeType)
set(OIS_ROOT ${THIRDPARTY_ROOT}/ois)
set(MYGUI_ROOT ${THIRDPARTY_ROOT}/MyGUI)
set(LOG4CPP_ROOT ${THIRDPARTY_ROOT}/log4cpp)



set(OGRENATIVE_ROOT ${OGRESDK_ROOT}/ogrenative)
include_directories(${OGRENATIVE_ROOT})


add_library( # Sets the name of the library.
             ogrenative

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).

             ${OGRENATIVE_ROOT}/NativeActivity.cpp
             ${OGRENATIVE_ROOT}/Android.cpp
             ${OGRENATIVE_ROOT}/AndroidMain.cpp )


# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       ogrenative

                       # Links the target library to the log library
                       # included in the NDK.
                       log
                       dl
                       z
                       android
                       EGL
                       GLESv2
                        )