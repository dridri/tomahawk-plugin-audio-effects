cmake_minimum_required(VERSION 2.6)

qt_wrap_ui( Loudness_UI loudness.ui )

tomahawk_add_plugin(loudness
    TYPE filter
    EXPORT_MACRO TOMAHAWK_VIEWPAGE_EXPORT_PRO
    SOURCES
        ${Loudness_UI}
        Loudness.cpp
    LINK_LIBRARIES
        ${TOMAHAWK_LIBRARIES}
)
