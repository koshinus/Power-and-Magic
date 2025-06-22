# Setup requirement for this build file.
CMAKE_MINIMUM_REQUIRED(VERSION 3.12 FATAL_ERROR)
# Setup project name.
PROJECT(PowerAndMagic)

SET(CMAKE_CXX_STANDARD 20)

# Add godot-cpp as part of this multi-project build.
ADD_SUBDIRECTORY(3rdparty/expected)
# Add godot-cpp as part of this multi-project build.
ADD_SUBDIRECTORY(3rdparty/godot-cpp)
# Add the extension as part of this multi-project build.
ADD_SUBDIRECTORY(extensions)
