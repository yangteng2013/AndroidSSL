# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)


SET(SSL_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/openssl)

message(openssl-lib目录：${SSL_LIB_PATH})

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             hhssl

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/NativeSSL.cpp
             src/main/cpp/MD5.cpp
             src/main/cpp/AES.cpp
             )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

#${ANDROID_ABI}
target_link_libraries( # Specifies the target library.
                       hhssl

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}

                       ${SSL_LIB_PATH}/lib/libssl.a
                       ${SSL_LIB_PATH}/lib/libcrypto.a

                       )


include_directories(
                  ${SSL_LIB_PATH}/include
                  )