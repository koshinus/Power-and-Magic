# Setup requirement for this build file.
CMAKE_MINIMUM_REQUIRED(VERSION 3.12 FATAL_ERROR)
# Setup project name.
PROJECT(pwmlibs)
# Calculate target bit count if not given. 
# This is also used in GDExtension platform specifiers due to the possibility of
# having separate builds for multiple different platforms.
IF (NOT DEFINED BITS)
  MATH(EXPR BITS "8*${CMAKE_SIZEOF_VOID_P}")
ENDIF()

SET(TARGET_BUILD_TYPE ${CMAKE_BUILD_TYPE})
STRING(TOLOWER ${TARGET_BUILD_TYPE} TARGET_BUILD_TYPE)


if(CMAKE_SYSTEM_NAME MATCHES "iOS")
	SET(TARGET "${PROJECT_NAME}.${CMAKE_SYSTEM_NAME}.template_${TARGET_BUILD_TYPE}")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
	SET(TARGET "${PROJECT_NAME}.linux.template_${TARGET_BUILD_TYPE}.arm${BITS}")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "riscv")
	SET(TARGET "${PROJECT_NAME}.linux.template_${TARGET_BUILD_TYPE}.rv${BITS}")
elseif(UNIX AND NOT APPLE)
	SET(TARGET "${PROJECT_NAME}.linux.template_${TARGET_BUILD_TYPE}.x86_${BITS}")
elseif(WIN32)
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        SET(TARGET "lib${PROJECT_NAME}.windows.template_${TARGET_BUILD_TYPE}.x86_${BITS}")
  else()
        SET(TARGET "${PROJECT_NAME}.windows.template_${TARGET_BUILD_TYPE}.x86_${BITS}")
  endif()
else()
	SET(TARGET "unknown" PARENT_SCOPE)
endif()

# Make it lower case.
STRING(TOLOWER ${TARGET} TARGET)
# Find all cpp files and put those in SOURCES variable.
FILE(GLOB_RECURSE SOURCES src/*.c** src/*.h**)
#FILE(GLOB_RECURSE SOURCES
#              src/utils/*
              #src/hero/hero_info_impl.hpp
#              src/test_node_impl.cpp src/test_node_impl.hpp
              #src/skills/skill_button_impl.cpp src/skills/skill_button_impl.hpp
#              src/main_menu_impl.cpp src/main_menu_impl.hpp
#              src/register_types.cpp src/register_types.hpp
#)
# Create build target from the name and sources we setup above.
ADD_LIBRARY(${TARGET} SHARED ${SOURCES})
# Add godot::cpp as private dependency.
TARGET_LINK_LIBRARIES(${TARGET} PRIVATE godot::cpp)
TARGET_LINK_LIBRARIES(${TARGET} PRIVATE expected)

# If we are using Visual Studio compiler, add some options.
IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # Enable C++20 support.
  TARGET_COMPILE_OPTIONS(${TARGET} PRIVATE /std:c++20)
  #TARGET_COMPILE_OPTIONS(${TARGET} PRIVATE /std:c++20 /GR-)
  IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
    # If target is debug build, setup proper runtime library (mainly to match godot-cpp one).
    SET(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
  ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)
ELSE()
  #TARGET_COMPILE_OPTIONS(${TARGET} PRIVATE -std=c++20 -fno-rtti)
ENDIF()
# Create a proper GDExtension configuration filename.
STRING(TOLOWER "${PROJECT_NAME}.gdextension" GDEXTENSION_CONFIGURATION_FILE)
# Create entry point name from project name.
STRING(TOLOWER ${PROJECT_NAME} GDEXTENSION_ENTRY_POINT)
# Create GDExtension configuration file from our configuration template.
CONFIGURE_FILE(gdextension.in ${GDEXTENSION_CONFIGURATION_FILE})
# Specify runtime installation target (this is the actual library).
INSTALL(TARGETS ${TARGET} CONFIGURATIONS Debug RUNTIME DESTINATION ${PROJECT_NAME})
# Specify files installation target (this is the configuration file).
INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/${GDEXTENSION_CONFIGURATION_FILE}" CONFIGURATIONS Release Debug DESTINATION ${PROJECT_NAME})
