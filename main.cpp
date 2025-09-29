#include <iostream>
#include "./include/bitstring.h"

int main() {
    BitString initList = {1, 0, 1, 1, 0}; 
    std::cout << "Битовая строка из списка: ";
    initList.print(std::cout) << std::endl;
        
    // BitString fromString("123"); 
    // std::cout << "Битовая строка из строки: ";
    // fromString.print(std::cout) << std::endl;
    // initList.oper2(fromString);
    // initList.print(std::cout) << std::endl;
    // дописать примерчики
    try {
        BitString fromString("123"); 
        std::cout << "Битовая строка из строки: ";

    } catch (std::exception& exception) {
        std::cerr << "Перехвачено исключение: " << exception.what() << std::endl;
    }
}