# define minimum cmake version
cmake_minimum_required(VERSION 3.3)

set( MOSAIC_LIB_NAME  MosaicObjectTemplate )

PROJECT(${MOSAIC_LIB_NAME})

# ------------------------ OF Path -----------------------
#
# This MUST be a RELATIVE path to OF!!!
set( OF_DIRECTORY_BY_USER "../../of_v0.10.0_osx_release" )

# --------------------- Source Files ---------------------

include_directories(${OF_DIRECTORY_BY_USER}/addons/ofxVisualProgramming/src)
include_directories(${OF_DIRECTORY_BY_USER}/addons/ofxVisualProgramming/src/core)
include_directories(${OF_DIRECTORY_BY_USER}/addons/ofxVisualProgramming/libs/pugg)

set(SOURCES plugin.cpp MosaicObjectTemplate.h MosaicObjectTemplate.cpp)

add_library(${MOSAIC_LIB_NAME} SHARED ${SOURCES})


# ------------------------ AddOns  -----------------------

set( OFX_ADDONS_ACTIVE
         ofxAssimpModelLoader
         ofxGui
         ofxNetwork
         ofxOpenCv
         ofxOsc
         ofxSvg
         ofxVectorGraphics
         ofxXmlSettings
         ofxAudioFile
         ofxDatGui
         ofxFontStash
         ofxGLEditor
         ofxLua
         ofxMidi
         ofxPDSP
         ofxPython
         ofxThreadedFileDialog
         )


# =========================================================================
# ============================== OpenFrameworks ===========================
# =========================================================================
# ============================================================================
# ---------------------------------- PATHS -----------------------------------
# ============================================================================
# --- Set an absolute path name, in case the project used a relative one
get_filename_component(OF_DIRECTORY_ABSOLUTE ${OF_DIRECTORY_BY_USER} ABSOLUTE)
set(CMAKE_PATH_NAME addons/ofxCMake)
set(OF_CMAKE_MODULES ${OF_DIRECTORY_ABSOLUTE}/${CMAKE_PATH_NAME}/modules)
set(OF_CMAKE_ADDONS ${OF_DIRECTORY_ABSOLUTE}/${CMAKE_PATH_NAME}/addOns)
set(OF_CMAKE_LIBS ${OF_DIRECTORY_ABSOLUTE}/${CMAKE_PATH_NAME}/libs)


# ============================================================================
# --------------------------------- ADDONS -----------------------------------
# --- Include all addOn .cmake files.
# --- Libs are only linked, if set in the project CMakeLists.txt
# ============================================================================
include(${OF_CMAKE_MODULES}/addOns.cmake)


# ============================================================================
# -------------------------------- OF SOURCE FILES ---------------------------
# ============================================================================
include(${OF_CMAKE_MODULES}/openFrameworks.cmake)

if (APPLE) # Apple is a Unix, too. So dont ask only first UNIX
    include(${OF_CMAKE_MODULES}/openFrameworksApple.cmake)
elseif (UNIX)
    include(${OF_CMAKE_MODULES}/openFrameworksLinux.cmake)
elseif (WIN32)
    include(${OF_CMAKE_MODULES}/openFrameworksWindows.cmake)
else ()
    message(FATAL_ERROR "Operating System not supported")
endif ()


# ============================================================================
# -------------------------------- OF CONFIGURATION --------------------------
# ============================================================================
include(${OF_CMAKE_MODULES}/config.cmake)

if (APPLE)
  set(CMAKE_C_FLAGS "") # -x objective-c
  set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ -D__MACOSX_CORE__")
  set_source_files_properties(${OF_SOURCE_FILES} PROPERTIES COMPILE_FLAGS "-x objective-c++")
  add_compile_options(-Wno-deprecated-declarations)

  find_program(CCACHE_FOUND ccache)
  if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
  endif(CCACHE_FOUND)
elseif (UNIX)
    set_source_files_properties( ${OF_SOURCE_FILES} PROPERTIES COMPILE_FLAGS "-std=c++11 -Wall -fPIC" )
elseif (WIN32)

else ()
    message(FATAL_ERROR "Operating System not supported")
endif ()
# =========================================================================
