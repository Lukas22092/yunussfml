#include <gtest/gtest.h>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

TEST(BasicTest, AssertTrue) {
    ASSERT_TRUE(true);
}

TEST(NotSoBasicTest, AssertFalse) {
    ASSERT_FALSE(false);
}
