#include <gtest/gtest.h>
#include "../include/bitstring.h"


TEST(BitStringTest, test_convet_to_decimal1) {
    BitString bs;
    EXPECT_EQ(bs.convert_to_decimal(), 0);
}

TEST(BitStringTest, test_convet_to_decimal2) {
    BitString bs(5, 1);  
    EXPECT_EQ(bs.convert_to_decimal(), 31); // 11111 = 31
}

TEST(BitStringTest, test_constructor1) {
    EXPECT_THROW(BitString(5, 2), std::invalid_argument);
}

TEST(BitStringTest, test_constructor2) {
    BitString bs({1,0,1,1});
    EXPECT_EQ(bs.convert_to_decimal(), 11); // 1011 = 11
}

TEST(BitStringTest, test_constructor3) {
    EXPECT_THROW(BitString({0,2,1}), std::invalid_argument);
}

TEST(BitStringTest, test_constructor4) {
    BitString bs("1010");
    EXPECT_EQ(bs.convert_to_decimal(), 10);
}

TEST(BitStringTest, test_constructor5) {
    EXPECT_THROW(BitString("10a1"), std::invalid_argument);
}

TEST(BitStringTest, test_constructor6) {
    BitString bs1("1101");
    BitString bs2(bs1);
    EXPECT_EQ(bs1.convert_to_decimal(), bs2.convert_to_decimal());
}

TEST(BitStringTest, test_constructor7) {
    BitString bs1("111");
    BitString bs2(std::move(bs1));
    EXPECT_EQ(bs2.convert_to_decimal(), 7);
}

TEST(BitStringTest, test_removing_leading_zeros) {
    BitString bs("000101");
    bs.removing_leading_zeros();
    EXPECT_EQ(bs.convert_to_decimal(), 5);
}

TEST(BitStringTest, test_add) {
    BitString bs1("1011"); // 11
    BitString bs2("110");  // 6
    BitString result = bs1.add(bs2);
    EXPECT_EQ(result.convert_to_decimal(), 17);
}

TEST(BitStringTest, test_remove) {
    BitString bs1("1011"); // 11
    BitString bs2("10");   // 2
    BitString result = bs1.remove(bs2);
    EXPECT_EQ(result.convert_to_decimal(), 9);
}

TEST(BitStringTest, test_copy) {
    BitString bs1("1111");
    BitString bs2 = bs1.copy();
    EXPECT_EQ(bs2.convert_to_decimal(), 15);
}

TEST(BitStringTest, test_more) {
    BitString bs1("1010"); // 10
    BitString bs2("1001"); // 9
    EXPECT_TRUE(bs1.more(bs2));
}

TEST(BitStringTest, test_equally) {
    BitString bs1("111");
    BitString bs2("111");
    EXPECT_TRUE(bs1.equally(bs2));
}

TEST(BitStringTest, test_AND) {
    BitString bs1("1101"); // 13
    BitString bs2("1011"); // 11
    BitString result = bs1.AND(bs2);
    EXPECT_EQ(result.convert_to_decimal(), 9); // 1001
}

TEST(BitStringTest, test_OR) {
    BitString bs1("1101"); // 13
    BitString bs2("1011"); // 11
    BitString result = bs1.OR(bs2);
    EXPECT_EQ(result.convert_to_decimal(), 15); // 1111
}

TEST(BitStringTest, test_XOR) {
    BitString bs1("1101"); // 13
    BitString bs2("1011"); // 11
    BitString result = bs1.XOR(bs2);
    EXPECT_EQ(result.convert_to_decimal(), 6); // 0110
}

TEST(BitStringTest, test_NOT) {
    BitString bs1("1010");
    BitString result = bs1.NOT();
    EXPECT_EQ(result.convert_to_decimal(), 5); // ~1010 = 0101
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}