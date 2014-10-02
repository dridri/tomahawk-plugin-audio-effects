cmake_minimum_required(VERSION 2.6)

tomahawk_add_plugin(equalizer
    TYPE filter
    EXPORT_MACRO TOMAHAWK_VIEWPAGE_EXPORT_PRO
    SOURCES
        Equalizer.cpp
    LINK_LIBRARIES
        ${TOMAHAWK_LIBRARIES}
)
