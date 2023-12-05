QT += testlib
QT -= gui

CONFIG += c++17 console qt warn_on no_testcase_installs testcase
CONFIG -= app_bundle release

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
SOURCES += \
    MemoryManagement/ThirdParty/lz4.c

HEADERS += \
    CoreComponents/global.hpp \
    DeviceManagement/GPS/device_gps_generic.hpp \
    DeviceManagement/GPS/device_gps_nmea.hpp \
    DeviceManagement/GPS/device_gps_pmtk.hpp \
    DeviceManagement/device_base.hpp \
    MemoryManagement/ThirdParty/lz4.h \
    MemoryManagement/linked_list.hpp \
    MemoryManagement/memory_compression.hpp \
    MemoryManagement/memory_pool.hpp \
    MemoryManagement/ring_buffer.hpp

INCLUDEPATH += \
    CoreComponents \
    DeviceManagement \
    DeviceManagement/GPS \
    MemoryManagement \
    MemoryManagement/ThirdParty \
    SignalProcessing

TEMPLATE = subdirs
SUBDIRS += \
    MemoryManagement/linked_list_test/linked_list_test.pro \
    MemoryManagement/memory_compression_test/memory_compression_test.pro \
    MemoryManagement/memory_pool_test/memory_pool_test.pro \
    MemoryManagement/ring_buffer_test/ring_buffer_test.pro \

