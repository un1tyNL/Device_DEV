#if defined(QT_TESTLIB_LIB)
#define TEST_CASE(object, testcase) void object::testcase()
#else
#undef QVERIFY
#define QVERIFY ASSERT_TRUE
#undef QCOMPARE
#define QCOMPARE                    ASSERT_EQ
#define TEST_CASE(object, testcase) TEST(object, testcase)
#endif
