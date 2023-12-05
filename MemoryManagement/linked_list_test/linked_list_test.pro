QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle release

TEMPLATE = app

SOURCES += \
    linked_list_test.cpp

HEADERS += \
    ../linked_list.hpp \

INCLUDEPATH += \
    ../../CoreComponents \
    ../MemoryManagement \
