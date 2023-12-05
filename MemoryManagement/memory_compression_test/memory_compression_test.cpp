#include "../linked_list.hpp"
#include "../../Tools/Testing/test_helper.hpp"

#if defined(QT_TESTLIB_LIB)
#include <QCoreApplication>
#include <QtTest/QtTest>
#else
#include "gtest/gtest.h"
#endif

#if defined(QT_TESTLIB_LIB)
class TestMemoryCompression : public QObject
{
  Q_OBJECT

private slots:

};
#endif

#if defined(QT_TESTLIB_LIB)
QTEST_GUILESS_MAIN(TestMemoryCompression)
#include "memory_compression_test.moc"
#endif
