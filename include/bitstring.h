#pragma once
#include <initializer_list>
#include <string>
#include <iostream>
#include <math.h>

class BitString {
private:
    size_t arraySize;           
    unsigned char* dataArray;   
public:
    BitString();
    BitString(const size_t& n, unsigned char t = 0);
    BitString(const std::initializer_list<unsigned char>& t);
    BitString(const std::string& t);
    BitString(const BitString& other);
    BitString(BitString&& other) noexcept;

    BitString add(const BitString& other);
    BitString remove(const BitString& other);
    BitString copy();

    bool more(const BitString& other);
    bool less(const BitString& other);
    bool equally(const BitString& other);

    BitString oper1(const BitString& other);  //+=
    BitString oper2(const BitString& other); //-=

    BitString AND(const BitString& other);
    BitString OR(const BitString& other);
    BitString XOR(const BitString& other);
    BitString NOT();

    double convert_to_decimal() const;
    void removing_leading_zeros();

    std::ostream& print(std::ostream& outputStream);
    
    virtual ~BitString() noexcept;
};