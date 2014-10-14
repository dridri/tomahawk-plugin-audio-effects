cmake_minimum_required(VERSION 2.8)
CMAKE_POLICY(SET CMP0017 NEW)

set (CMAKE_CXX_FLAGS "-g3 -Wall") 

if(NOT TOMAHAWK_LIBRARIES)
    message(STATUS "BUILDING OUTSIDE TOMAHAWK")
    find_package(Tomahawk REQUIRED)
else()
    message(STATUS "BUILDING INSIDE TOMAHAWK")
    set(TOMAHAWK_USE_FILE "${CMAKE_SOURCE_DIR}/TomahawkUse.cmake")
endif()
include( ${TOMAHAWK_USE_FILE} )

include_directories( ${TOMAHAWK_INCLUDE_DIRS} )
include_directories( ${CMAKE_SOURCE_DIR}/include )
include_directories( ${CMAKE_SOURCE_DIR}/src )

qt_wrap_ui( EqPlugin_UI effects.ui )

tomahawk_add_plugin(dsp
    TYPE viewpage
    EXPORT_MACRO TOMAHAWK_VIEWPAGE_EXPORT_PRO
    SOURCES
        ${EqPlugin_UI}
        src/DspPlugin.cpp
        src/DspWidget.cpp
        src/DspGraph.cpp
        resources.qrc
    LINK_LIBRARIES
        ${TOMAHAWK_LIBRARIES}
        ${QT_QTOPENGL_LIBRARIES}
        ${OPENGL_LIBRARIES}
        -lfftw3f -g3
)

add_subdirectory( plugins/equalizer )
add_subdirectory( plugins/loudness )

install(TARGETS tomahawk_viewpage_dsp DESTINATION /usr/local/lib)
