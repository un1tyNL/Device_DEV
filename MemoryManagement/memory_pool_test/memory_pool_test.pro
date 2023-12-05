QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle release

TEMPLATE = app

SOURCES +=  \
    memory_pool_test.cpp

HEADERS += \
    ../memory_pool.hpp \
    ../../CoreComponents/global.hpp \

INCLUDEPATH += \
    ../../CoreComponents \
    ../MemoryManagement \
