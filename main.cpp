#include <iostream>
#include <iterator>
#include <ostream>
#include "./include/bitstring.h"

int main() {
    BitString bs1;
    BitString bs2(10, 1);
    BitString bs3{1, 0, 1, 0, 1, 0};
    BitString bs4("101001");
    BitString bs5(bs4);
    BitString bs6(std::move(bs5));
    bs1.print(std::cout) << std::endl;
    bs2.print(std::cout) << std::endl;
    bs3.print(std::cout) << std::endl;
    bs4.print(std::cout) << std::endl;
    bs5.print(std::cout) << std::endl;

    bs5.print(std::cout) << std::endl;
    bs6.print(std::cout) << std::endl;
    std::cout << "==========================" << std::endl;
    BitString bs7{1, 0, 1, 1};
    BitString bs8{1, 1, 1, 0};
    BitString bs9(bs7.add(bs8));
    bs9.print(std::cout) << std::endl;
    BitString bs10("000000101");
    bs10.print(std::cout) << std::endl;
    bs10.rm_leading_zeros();
    bs10.print(std::cout) << std::endl;
    std::cout << bs10.convert_to_decimal() << std::endl;
    BitString bs11(bs7.add(bs8));
    std::cout << bs7.convert_to_decimal() << std::endl;
    std::cout << bs8.convert_to_decimal() << std::endl;
    bs11.print(std::cout) << std::endl;
    std::cout << bs11.convert_to_decimal() << std::endl;
    BitString bs12(bs8.remove(bs7));
    std::cout << bs12.convert_to_decimal() << std::endl;
    BitString bs13("111");
    BitString bs14("110");
    std::cout << bs13.more(bs14) << std::endl;
    std::cout << bs13.less(bs14) << std::endl;
    std::cout << bs13.equally(bs14) << std::endl;
    bs13.oper1(bs14);
    bs13.print(std::cout) << std::endl;
    bs13.oper2(bs14);
    bs13.print(std::cout) << std::endl;
    // BitString bs7{1, 0, 1, 1};
    // BitString bs8{1, 1, 1, 0};
    BitString bs15(bs7.AND(bs8));
    bs15.print(std::cout) << std::endl;
    BitString bs16(bs7.OR(bs8));
    bs16.print(std::cout) << std::endl;
    bs7.NOT().print(std::cout) << std::endl;
    BitString bs17(bs7.XOR(bs8));
    bs17.print(std::cout) << std::endl;
}