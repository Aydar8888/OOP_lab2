#include <gtest/gtest.h>
#include <utility>
#include "../include/bitstring.h"

// тесты конструкторов
TEST(BitStringTest, test_constructor1) {
    BitString bs;
    EXPECT_EQ(bs.convert_to_decimal(), 0);
}

TEST(BitStringTest, test_constructor2) {
    BitString bs1(5);
    BitString bs2(5, 1); // 11111 = 31
    BitString bs3(0);
    BitString bs4(30, 1);
    BitString bs5(0, 0);
    BitString bs6(0, 1);
    EXPECT_EQ(bs1.convert_to_decimal(), 0);
    EXPECT_EQ(bs2.convert_to_decimal(), 31);
    EXPECT_EQ(bs3.convert_to_decimal(), 0);
    EXPECT_EQ(bs4.convert_to_decimal(), 1073741823);
    EXPECT_EQ(bs5.convert_to_decimal(), 0);
    EXPECT_EQ(bs6.convert_to_decimal(), 0);
    EXPECT_THROW(BitString(5, 2), std::invalid_argument);
    EXPECT_THROW(BitString(0, 10), std::invalid_argument);
}

TEST(BitStringTest, test_constructor3) {
    BitString bs1{0};
    BitString bs2{1};
    BitString bs3{};
    BitString bs4{1, 0, 1}; // 5
    BitString bs5{0, 0, 1}; // 1
    BitString bs6{0, 0, 0, 0, 0}; 
    BitString bs7{0, 0, 1, 0, 1, 1}; // 11
    BitString bs8{1, 0, 0, 0}; // 8
    EXPECT_EQ(bs1.convert_to_decimal(), 0);
    EXPECT_EQ(bs2.convert_to_decimal(), 1);
    EXPECT_EQ(bs3.convert_to_decimal(), 0);
    EXPECT_EQ(bs4.convert_to_decimal(), 5);
    EXPECT_EQ(bs5.convert_to_decimal(), 1);
    EXPECT_EQ(bs6.convert_to_decimal(), 0);
    EXPECT_EQ(bs7.convert_to_decimal(), 11);
    EXPECT_EQ(bs8.convert_to_decimal(), 8);
    EXPECT_THROW(BitString({1, 2, 3, 4, 5}), std::invalid_argument);
}

TEST(BitStringTest, test_constructor4) {
    BitString bs1("");
    BitString bs2("1");
    BitString bs3("0");
    BitString bs4("111"); //7
    BitString bs5("0000000000000000111");
    BitString bs6("10101"); // 21
    BitString bs7("0000000000010101");
    BitString bs8("111111111111111111111");
    EXPECT_EQ(bs1.convert_to_decimal(), 0);
    EXPECT_EQ(bs2.convert_to_decimal(), 1);
    EXPECT_EQ(bs3.convert_to_decimal(), 0);
    EXPECT_EQ(bs4.convert_to_decimal(), 7);
    EXPECT_EQ(bs5.convert_to_decimal(), 7);
    EXPECT_EQ(bs6.convert_to_decimal(), 21);
    EXPECT_EQ(bs7.convert_to_decimal(), 21);
    EXPECT_EQ(bs8.convert_to_decimal(), 2097151);
    EXPECT_THROW(BitString(" "), std::invalid_argument);
    EXPECT_THROW(BitString("0123"), std::invalid_argument);
}

TEST(BitStringTest, test_constructor5) {
    BitString bs1;
    BitString bs2(bs1);
    BitString bs3("111111111");
    BitString bs4(bs3);
    BitString bs5("1");
    BitString bs6({});
    BitString bs7(bs5);
    BitString bs8(bs6);
    BitString bs9("00001");
    BitString bs10(bs9);
    EXPECT_EQ(bs1.convert_to_decimal(), bs2.convert_to_decimal());
    EXPECT_EQ(bs4.convert_to_decimal(), 511);
    EXPECT_EQ(bs7.convert_to_decimal(), 1);
    EXPECT_EQ(bs8.convert_to_decimal(), 0);
    EXPECT_EQ(bs10.convert_to_decimal(), 1);
}

TEST(BitStringTest, test_constructor6) {
    BitString bs1(3, 1); //7
    BitString bs2(std::move(bs1));
    BitString bs3;
    BitString bs4(std::move(bs3));
    EXPECT_EQ(bs1.convert_to_decimal(), 0);
    EXPECT_EQ(bs2.convert_to_decimal(), 7);
    EXPECT_EQ(bs4.convert_to_decimal(), 0);
}

// тест суммы
TEST(BitStringTest, test_add) {
    BitString bs1("1");
    BitString bs2(bs1.add(bs1));
    BitString bs3;
    BitString bs4{1};
    BitString bs5(bs3.add(bs4));
    BitString bs6("1011"); // 11
    BitString bs7("110");  // 6
    BitString bs8(bs6.add(bs7));
    BitString bs9(bs7.add(bs6));
    BitString bs10("000111");
    BitString bs11(1, 1);
    BitString bs12(bs10.add(bs11));
    BitString bs13(bs11.add(bs10));
    BitString bs14{0, 0, 0, 0, 0, 0};
    BitString bs15{0, 0, 0};
    BitString bs16(bs14.add(bs15));
    EXPECT_EQ(bs2.convert_to_decimal(), 2);
    EXPECT_EQ(bs5.convert_to_decimal(), 1);
    EXPECT_EQ(bs8.convert_to_decimal(), 17);
    EXPECT_EQ(bs9.convert_to_decimal(), 17);
    EXPECT_EQ(bs12.convert_to_decimal(), 8);
    EXPECT_EQ(bs13.convert_to_decimal(), 8);
    EXPECT_EQ(bs16.convert_to_decimal(), 0);
}

// тест разности
TEST(BitStringTest, test_remove) {
    BitString bs1("1");
    BitString bs2(bs1.remove(bs1));
    BitString bs3;
    BitString bs4{1};
    BitString bs5("1011"); // 11
    BitString bs6("110");  // 6
    BitString bs7(bs5.remove(bs6));
    BitString bs8("000111");
    BitString bs9(1, 1);
    BitString bs10(bs8.remove(bs9));
    BitString bs11{0, 0, 0, 0, 0, 0};
    BitString bs12{0, 0, 0};
    BitString bs13(bs11.remove(bs12));
    EXPECT_EQ(bs2.convert_to_decimal(), 0);
    EXPECT_THROW(bs3.remove(bs4), std::invalid_argument);
    EXPECT_EQ(bs7.convert_to_decimal(), 5);
    EXPECT_EQ(bs10.convert_to_decimal(), 6);
    EXPECT_EQ(bs13.convert_to_decimal(), 0);
}


// проверка copy
TEST(BitStringTest, test_copy) {
    BitString bs1("1111");
    BitString bs2 = bs1.copy();
    EXPECT_EQ(bs2.convert_to_decimal(), 15);
}
 
// провекрка >
TEST(BitStringTest, test_more) {
    BitString bs1("1010"); // 10
    BitString bs2("1001"); // 9
    BitString bs3{0};
    BitString bs4{0};
    BitString bs5{1};
    BitString bs6{0};
    BitString bs7{0, 0, 0, 0, 0, 0};
    BitString bs8{0, 0, 0};

    EXPECT_TRUE(bs1.more(bs2));
    EXPECT_FALSE(bs3.more(bs3));
    EXPECT_FALSE(bs3.more(bs4));
    EXPECT_FALSE(bs4.more(bs5));
    EXPECT_TRUE(bs5.more(bs4));
    EXPECT_FALSE(bs7.more(bs8));
}

// проверка <
TEST(BitStringTest, test_less) {
    BitString bs1("1010"); // 10
    BitString bs2("1001"); // 9
    BitString bs3{0};
    BitString bs4{0};
    BitString bs5{1};
    BitString bs6{0};
    BitString bs7{0, 0, 0, 0, 0, 0};
    BitString bs8{0, 0, 0};

    EXPECT_FALSE(bs1.less(bs2));
    EXPECT_FALSE(bs3.less(bs3));
    EXPECT_FALSE(bs3.less(bs4));
    EXPECT_TRUE(bs4.less(bs5));
    EXPECT_FALSE(bs5.less(bs4));
    EXPECT_FALSE(bs7.less(bs8));
}

// ==
TEST(BitStringTest, test_equally) {
    BitString bs1("111");
    BitString bs2("111");
    BitString bs3("1010"); // 10
    BitString bs4("1001"); // 9
    BitString bs5{0};
    BitString bs6{0};
    BitString bs7{1};
    BitString bs8{0};
    BitString bs9{0, 0, 0, 0, 0, 0};
    BitString bs10{0, 0, 0};
    EXPECT_TRUE(bs1.equally(bs2));
    EXPECT_FALSE(bs3.equally(bs4));
    EXPECT_TRUE(bs5.equally(bs6));
    EXPECT_FALSE(bs7.equally(bs8));
    EXPECT_TRUE(bs9.equally(bs10));
}

// тест +=
TEST(BitStringTest, oper1) {
    BitString bs1("111");
    BitString bs2("101");
    bs1.oper1(bs2);
    BitString bs3;
    BitString bs4;
    bs3.oper1(bs4);
    EXPECT_EQ(bs1.convert_to_decimal(), 12);
    EXPECT_EQ(bs2.convert_to_decimal(), 5);
    EXPECT_EQ(bs3.convert_to_decimal(), 0);
}

// тест -=
TEST(BitStringTest, oper2) {
    BitString bs1("111");
    BitString bs2("101");
    bs1.oper2(bs2);
    BitString bs3;
    BitString bs4;
    bs3.oper2(bs4);
    EXPECT_EQ(bs1.convert_to_decimal(), 2);
    EXPECT_EQ(bs2.convert_to_decimal(), 5);
    EXPECT_EQ(bs3.convert_to_decimal(), 0);
}

// тесты битовых операций
TEST(BitStringTest, test_AND) {
    BitString bs1("1101");
    BitString bs2("1011");
    BitString bs3(bs1.AND(bs2));
    BitString bs4; 
    BitString bs5;
    BitString bs6(bs4.AND(bs5));
    BitString bs7("1");
    BitString bs8(bs7.AND(bs7));
    BitString bs9(bs7.AND(bs5));
    BitString bs10({0, 1, 1, 0, 0, 1});
    BitString bs11({0, 1, 1});
    BitString bs12(bs10.AND(bs11));
    EXPECT_EQ(bs3.convert_to_decimal(), 9); // 1001
    EXPECT_EQ(bs6.convert_to_decimal(), 0); 
    EXPECT_EQ(bs8.convert_to_decimal(), 1); 
    EXPECT_EQ(bs9.convert_to_decimal(), 0); 
    EXPECT_EQ(bs12.convert_to_decimal(), 1); 
}

TEST(BitStringTest, test_OR) {
    BitString bs1("1101"); // 13
    BitString bs2("1011"); // 11
    BitString bs3(bs1.OR(bs2));
    BitString bs4; 
    BitString bs5;
    BitString bs6(bs4.OR(bs5));
    BitString bs7("1");
    BitString bs8(bs7.OR(bs7));
    BitString bs9(bs7.OR(bs5));
    BitString bs10({0, 1, 1, 0, 0, 1});
    BitString bs11({0, 1, 1});
    BitString bs12(bs10.OR(bs11)); // 11011
    EXPECT_EQ(bs3.convert_to_decimal(), 15); // 1111
    EXPECT_EQ(bs6.convert_to_decimal(), 0); 
    EXPECT_EQ(bs8.convert_to_decimal(), 1); 
    EXPECT_EQ(bs9.convert_to_decimal(), 1);
    EXPECT_EQ(bs12.convert_to_decimal(), 27);
}

TEST(BitStringTest, test_XOR) {
    BitString bs1("1101"); // 13
    BitString bs2("1011"); // 11
    BitString bs3(bs1.XOR(bs2));
    BitString bs4; 
    BitString bs5;
    BitString bs6(bs4.XOR(bs5));
    BitString bs7("1");
    BitString bs8(bs7.XOR(bs7));
    BitString bs9(bs7.XOR(bs5));
    BitString bs10({0, 1, 1, 0, 0, 1});
    BitString bs11({0, 0, 0, 0, 1, 1});
    BitString bs12(bs10.XOR(bs11)); // 011010
    EXPECT_EQ(bs3.convert_to_decimal(), 6); // 0110
    EXPECT_EQ(bs6.convert_to_decimal(), 1); 
    EXPECT_EQ(bs8.convert_to_decimal(), 0); 
    EXPECT_EQ(bs9.convert_to_decimal(), 1);
    EXPECT_EQ(bs12.convert_to_decimal(), 26);

}

TEST(BitStringTest, test_NOT) {
    BitString bs1("1010");
    BitString bs2{0};
    BitString bs3{1};
    BitString bs4(bs1.NOT());
    BitString bs5(bs2.NOT());
    BitString bs6(bs3.NOT());
    EXPECT_EQ(bs4.convert_to_decimal(), 5); // ~1010 = 0101
    EXPECT_EQ(bs5.convert_to_decimal(), 1);
    EXPECT_EQ(bs6.convert_to_decimal(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}