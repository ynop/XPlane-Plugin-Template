cmake_minimum_required(VERSION 3.3)
set(PRODUCT_NAME XPlanePluginTemplate)
project(${PRODUCT_NAME})

# SOURCE FILES
set(SOURCE_FILES src/XPlugin.cpp src/XPlugin.h)

# COMPILER FLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(APPLE)
    add_executable(${PRODUCT_NAME} ${SOURCE_FILES})
elseif(WIN32)
    add_library(${PRODUCT_NAME} MODULE ${SOURCE_FILES})
endif()

# LIBRARIES
set(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED COMPONENTS filesystem system iostreams)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
target_link_libraries(${PRODUCT_NAME} ${Boost_LIBRARIES})

if(UNIX)
    include_directories(external/XPlaneSDK/CHeaders/XPLM)
elseif(WIN32)
    include_directories(external\\XPlaneSDK\\CHeaders\\XPLM)
endif()

# X-PLANE
# In order to use the 2.0 APIs, you need to define the symbol XPLM200. In order to use the 2.1 APIs, you need to define the symbol XPLM210.
# (Define both to use the most recent plugin APIs - the XPLM210 macro does not enable the XPLM200 macro.)
# Without this symbol, the new 2.0 SDK will default to only letting you use 1.0 APIs.
# This feature is designed to let you build 1.0 and 2.0 plugins from the same SDK header. If XPLM200 is not defined, you cannot accidentally use a 2.0 routine.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DXPLM200=1 -DXPLM210=1")

#You must define one of the macros APL, IBM, or LIN to 1, depending on the OS you are compiling for.
if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAPL=1 -DIBM=0 -DLIN=0")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAPL=0 -DIBM=0 -DLIN=1")
elseif(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAPL=0 -DIBM=1 -DLIN=0 -D_CRT_SECURE_NO_WARNINGS")
endif()

# LINKING
if(APPLE)
    find_library(XPLM_LIBRARY XPLM external/XPlaneSDK/Libraries/Mac)
    find_library(XPWIDGETS_LIBRARY XPWidgets external/XPlaneSDK/Libraries/Mac/)

    target_link_libraries(${PRODUCT_NAME} ${XPLM_LIBRARY})
    target_link_libraries(${PRODUCT_NAME} ${XPWIDGETS_LIBRARY})
elseif(WIN32)
    find_library(XPLM_LIBRARY XPLM_64 external\\XPlaneSDK\\Libraries\\Win)
    find_library(XPWIDGETS_LIBRARY XPWidgets_64 external\\XPlaneSDK\\Libraries\\Win)

    target_link_libraries(${PRODUCT_NAME} ${XPLM_LIBRARY})
    target_link_libraries(${PRODUCT_NAME} ${XPWIDGETS_LIBRARY})
endif()


# OUTPUT
set_target_properties(${PRODUCT_NAME} PROPERTIES PREFIX "${PRODUCT_NAME}_")
set_target_properties(${PRODUCT_NAME} PROPERTIES SUFFIX "")

#
# -fvisibility=hidden
# For GCC-based environemnts (X-Code for Mac and command-line Linux environments) the default behavior is to exoprt all non-static C functions out of your plugin.
# This is not what you want, and can cause serious compatibility problems for 32-bit plugins. To get around this, use
#
if(APPLE)
    set(PLUGIN_OUTPUT_FILENAME "mac.xpl")
    set_target_properties(${PRODUCT_NAME} PROPERTIES LINK_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}  -fPIC -fvisibility=hidden -bundle -framework OpenGL -framework Cocoa")
elseif(UNIX)
    set(PLUGIN_OUTPUT_FILENAME "lin.xpl")
    set_target_properties(${PRODUCT_NAME} PROPERTIES LINK_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -rdynamic -nodefaultlibs -undefined_warning -fPIC -fvisibility=hidden")
elseif(WIN32)
    set(PLUGIN_OUTPUT_FILENAME "win.xpl")
endif()

set_target_properties(${PRODUCT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib" )
set_target_properties(${PRODUCT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib" )
set_target_properties(${PRODUCT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib" )
set_target_properties(${PRODUCT_NAME} PROPERTIES OUTPUT_NAME "${PLUGIN_OUTPUT_FILENAME}")