#include "../memory_pool.hpp"
#include "../../Tools/Testing/test_helper.hpp"

#if defined(QT_TESTLIB_LIB)
#include <QCoreApplication>
#include <QtTest/QtTest>
#else
#include "gtest/gtest.h"
#endif

#if defined(QT_TESTLIB_LIB)
class testMemoryManagement : public QObject
{
  Q_OBJECT

private slots:

};
#endif

TEST_CASE(testMemoryPool, testMemoryBlockConstruction)
{

}

#if defined(QT_TESTLIB_LIB)
QTEST_MAIN(testMemoryManagement)
#include "memory_pool_test.moc"
#endif
