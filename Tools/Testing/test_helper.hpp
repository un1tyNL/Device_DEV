#pragma once
#if defined(QT_TESTLIB_LIB)
// QTest is being used; retain original QTest macros
#define TEST_CASE(object, testcase) void object::testcase()
#else
// Googletest is being used; map original QTest macros to GTest ones.
#define TEST_CASE(object, testcase) TEST(object, testcase)

// ========================
// Assertion Macros (ASSERT_*)
// ========================
// Basic Assertions
#undef QVERIFY
#define QVERIFY(condition) \
    ASSERT_TRUE(condition) << "QVERIFY failed: " #condition

#undef QVERIFY2
#define QVERIFY2(condition, message) \
    ASSERT_TRUE((condition)) << "QVERIFY2 failed: " #condition " | " << message

#undef QFAIL
#define QFAIL(msg) \
    FAIL() << "QFAIL: " << msg

#undef QCOMPARE
#define QCOMPARE(actual, expected) \
    ASSERT_EQ(actual, expected) << "QCOMPARE failed: " #actual " != " #expected

// Additional Assertions
#undef QCOMPARE_NE
#define QCOMPARE_NE(actual, expected) \
    ASSERT_NE(actual, expected) << "QCOMPARE_NE failed: " #actual " == " #expected

#undef QCOMPARE_LE
#define QCOMPARE_LE(actual, expected) \
    ASSERT_LE(actual, expected) << "QCOMPARE_LE failed: " #actual " > " #expected

#undef QCOMPARE_LT
#define QCOMPARE_LT(actual, expected) \
    ASSERT_LT(actual, expected) << "QCOMPARE_LT failed: " #actual " >= " #expected

#undef QCOMPARE_GE
#define QCOMPARE_GE(actual, expected) \
    ASSERT_GE(actual, expected) << "QCOMPARE_GE failed: " #actual " < " #expected

#undef QCOMPARE_GT
#define QCOMPARE_GT(actual, expected) \
    ASSERT_GT(actual, expected) << "QCOMPARE_GT failed: " #actual " <= " #expected

#undef QCOMPARE_STRING
#define QCOMPARE_STRING(actual, expected) \
    ASSERT_STREQ(actual.c_str(), expected.c_str()) << "QCOMPARE_STRING failed: \"" #actual "\" != \"" #expected "\""

#undef QCOMPARE_PTR
#define QCOMPARE_PTR(actual, expected) \
    ASSERT_EQ(actual, expected) << "QCOMPARE_PTR failed: " #actual " != " #expected

#undef QCOMPARE_CONTAINER
#define QCOMPARE_CONTAINER(actual, expected) \
    ASSERT_EQ(actual, expected) << "QCOMPARE_CONTAINER failed: Containers are not equal"

#undef QVERIFY_NOT_NULL
#define QVERIFY_NOT_NULL(ptr) \
    ASSERT_NE(ptr, nullptr) << "QVERIFY_NOT_NULL failed: " #ptr " is null"

// Floating Point Comparisons
#undef QCOMPARE_FLOAT
#define QCOMPARE_FLOAT(actual, expected, tolerance) \
    ASSERT_NEAR(actual, expected, tolerance) << "QCOMPARE_FLOAT failed: " #actual " != " #expected " within tolerance " #tolerance

#undef QCOMPARE_DOUBLE
#define QCOMPARE_DOUBLE(actual, expected, tolerance) \
    ASSERT_NEAR(actual, expected, tolerance) << "QCOMPARE_DOUBLE failed: " #actual " != " #expected " within tolerance " #tolerance

// Exception Handling
#undef QVERIFY_EXCEPTION_THROWN
#define QVERIFY_EXCEPTION_THROWN(statement, exception_type) \
    ASSERT_THROW(statement, exception_type) << "QVERIFY_EXCEPTION_THROWN failed: Expected exception " #exception_type

#undef QVERIFY_NO_EXCEPTION
#define QVERIFY_NO_EXCEPTION(statement) \
    try { \
        statement; \
    } catch (const std::exception& e) { \
        FAIL() << "QVERIFY_NO_EXCEPTION failed: Unexpected exception thrown: " << e.what(); \
    } catch (...) { \
        FAIL() << "QVERIFY_NO_EXCEPTION failed: Unexpected non-standard exception thrown"; \
    }

// ========================
// Expectation Macros (EXPECT_*)
// ========================
// Basic Expectations
#undef QEXPECT_TRUE
#define QEXPECT_TRUE(condition) \
    EXPECT_TRUE(condition) << "QEXPECT_TRUE failed: " #condition

#undef QEXPECT_FALSE
#define QEXPECT_FALSE(condition) \
    EXPECT_FALSE(condition) << "QEXPECT_FALSE failed: " #condition

#undef QEXPECT_EQ
#define QEXPECT_EQ(actual, expected) \
    EXPECT_EQ(actual, expected) << "QEXPECT_EQ failed: " #actual " != " #expected

#undef QEXPECT_NE
#define QEXPECT_NE(actual, expected) \
    EXPECT_NE(actual, expected) << "QEXPECT_NE failed: " #actual " == " #expected

#undef QEXPECT_LE
#define QEXPECT_LE(actual, expected) \
    EXPECT_LE(actual, expected) << "QEXPECT_LE failed: " #actual " > " #expected

#undef QEXPECT_LT
#define QEXPECT_LT(actual, expected) \
    EXPECT_LT(actual, expected) << "QEXPECT_LT failed: " #actual " >= " #expected

#undef QEXPECT_GE
#define QEXPECT_GE(actual, expected) \
    EXPECT_GE(actual, expected) << "QEXPECT_GE failed: " #actual " < " #expected

#undef QEXPECT_GT
#define QEXPECT_GT(actual, expected) \
    EXPECT_GT(actual, expected) << "QEXPECT_GT failed: " #actual " <= " #expected

// String Expectations
#undef QEXPECT_STRING
#define QEXPECT_STRING(actual, expected) \
    EXPECT_STREQ(actual.c_str(), expected.c_str()) << "QEXPECT_STRING failed: \"" #actual "\" != \"" #expected "\""

// Pointer Expectations
#undef QEXPECT_PTR
#define QEXPECT_PTR(actual, expected) \
    EXPECT_EQ(actual, expected) << "QEXPECT_PTR failed: " #actual " != " #expected

// Container Expectations
#undef QEXPECT_CONTAINER
#define QEXPECT_CONTAINER(actual, expected) \
    EXPECT_EQ(actual, expected) << "QEXPECT_CONTAINER failed: Containers are not equal"

// Floating Point Expectations
#undef QEXPECT_FLOAT_NEAR
#define QEXPECT_FLOAT_NEAR(actual, expected, tolerance) \
    EXPECT_NEAR(actual, expected, tolerance) << "QEXPECT_FLOAT_NEAR failed: " #actual " != " #expected " within tolerance " #tolerance

#undef QEXPECT_DOUBLE_NEAR
#define QEXPECT_DOUBLE_NEAR(actual, expected, tolerance) \
    EXPECT_NEAR(actual, expected, tolerance) << "QEXPECT_DOUBLE_NEAR failed: " #actual " != " #expected " within tolerance " #tolerance

// Exception Handling Expectations
#undef QEXPECT_THROW
#define QEXPECT_THROW(statement, exception_type) \
    EXPECT_THROW(statement, exception_type) << "QEXPECT_THROW failed: Expected exception " #exception_type

#undef QEXPECT_NO_THROW
#define QEXPECT_NO_THROW(statement) \
    EXPECT_NO_THROW(statement) << "QEXPECT_NO_THROW failed: Unexpected exception thrown"

// ========================
// Message Macros
// ========================
#undef QINFO
#define QINFO(message) \
    std::cout << "QINFO: " << message << std::endl

#undef QDEBUG
#define QDEBUG(message) \
    std::cout << "QDEBUG: " << message << std::endl

#undef QTRACE
#define QTRACE(message) \
    std::cout << "QTRACE: " << message << std::endl

// ========================
// File and Directory Assertions
// ========================
#undef QASSERT_FILE_EXISTS
#define QASSERT_FILE_EXISTS(path) \
    ASSERT_TRUE(std::filesystem::exists(path)) << "QASSERT_FILE_EXISTS failed: " #path " does not exist"

#undef QEXPECT_FILE_EXISTS
#define QEXPECT_FILE_EXISTS(path) \
    EXPECT_TRUE(std::filesystem::exists(path)) << "QEXPECT_FILE_EXISTS failed: " #path " does not exist"

#undef QASSERT_DIR_EXISTS
#define QASSERT_DIR_EXISTS(path) \
    ASSERT_TRUE(std::filesystem::is_directory(path)) << "QASSERT_DIR_EXISTS failed: " #path " is not a directory"

#undef QEXPECT_DIR_EXISTS
#define QEXPECT_DIR_EXISTS(path) \
    EXPECT_TRUE(std::filesystem::is_directory(path)) << "QEXPECT_DIR_EXISTS failed: " #path " is not a directory"

// ========================
// Custom Matchers
// ========================
#undef QEXPECT_WITHIN_RANGE
#define QEXPECT_WITHIN_RANGE(actual, lower, upper) \
    EXPECT_TRUE((actual) >= (lower) && (actual) <= (upper)) << "QEXPECT_WITHIN_RANGE failed: " #actual " not within [" #lower ", " #upper "]"

// ========================
// Warning and Skip Macros
// ========================
#undef QWARN
#define QWARN(message) \
    std::cout << "QWARN: " << message << std::endl

#undef QSKIP
#define QSKIP(message) \
    GTEST_SKIP() << "QSKIP: " << message

#endif // defined(QT_TESTLIB_LIB)
