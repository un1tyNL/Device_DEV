QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle release

TEMPLATE = app

SOURCES +=  \
    ring_buffer_test.cpp \

HEADERS += \
    ../ring_buffer.hpp \
    ../../CoreComponents/global.hpp \

INCLUDEPATH += \
    ../../CoreComponents \
    ../MemoryManagement \
