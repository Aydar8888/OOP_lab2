#pragma once
#include <initializer_list>
#include <string>
#include <iostream>
#include <cmath>
#define MAX(a, b) ((a) > (b) ? (a) : (b))

class BitString {
private:
    size_t arraySize; //размер массива
    unsigned char* dataArray; //указатель на динасический массив
public:
    BitString(); // конструктор по умолчанию
    BitString(const size_t& n, unsigned char t = 0); // размер + значение по умолчанию
    BitString(const std::initializer_list<unsigned char>& t); //конструктор из списка инициализации
    BitString(const std::string& t); // из строки
    BitString(const BitString& other); // копирующий
    BitString(BitString&& other) noexcept; // перемщающий

    BitString add(const BitString& other); // сложение
    BitString remove(const BitString& other); // вычитание
    BitString copy();

    bool more(const BitString& other); // больше
    bool less(const BitString& other); // меньше
    bool equally(const BitString& other); // равно

    BitString oper1(const BitString& other);  //+=
    BitString oper2(const BitString& other); //-=

    BitString AND(const BitString& other); 
    BitString OR(const BitString& other);
    BitString XOR(const BitString& other);
    BitString NOT();

    void rm_leading_zeros(); // ведущие нули
    unsigned char last_bit(size_t p) const;
    int compare(const BitString &other) const;
    double convert_to_decimal() const;

    std::ostream& print(std::ostream& outputStream); // вывод в поток
    
    virtual ~BitString() noexcept; // диструктор
};