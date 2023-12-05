QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle release

TEMPLATE = app

SOURCES +=  \
    memory_compression_test.cpp \
    ../ThirdParty/lz4.c

HEADERS += \
    ../compress_data.hpp \
    ../../CoreComponents/global.hpp \
    ../ThirdParty/lz4.h

INCLUDEPATH += \
    ../../CoreComponents \
    ../MemoryManagement \
