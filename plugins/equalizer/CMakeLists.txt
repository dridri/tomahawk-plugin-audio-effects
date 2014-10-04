cmake_minimum_required(VERSION 2.6)

qt_wrap_ui( Equalizer_UI equalizer.ui )

tomahawk_add_plugin(equalizer
    TYPE filter
    EXPORT_MACRO TOMAHAWK_VIEWPAGE_EXPORT_PRO
    SOURCES
        ${Equalizer_UI}
        Equalizer.cpp
        GraphicEq.cpp
        fft3.c
    LINK_LIBRARIES
        ${TOMAHAWK_LIBRARIES}
        -lfftw3f
)
