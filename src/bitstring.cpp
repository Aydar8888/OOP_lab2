#include "../include/bitstring.h"

// конструктор по умолчанию
BitString::BitString() : arraySize(0), dataArray(nullptr) {}

// конструктор с заполнением
BitString::BitString(const size_t& arraySize, unsigned char defaultValue) {
    if (defaultValue != 0 && defaultValue != 1) {
        throw std::invalid_argument("Битовая строка может сотстоять только из 0 или 1");
    }
    this->arraySize = arraySize;
    this->dataArray = new unsigned char[arraySize];
    for (size_t i {0}; i < arraySize; ++i) {
        this->dataArray[i] = defaultValue;
    }
}

// конструктор из списка инициализации
BitString::BitString(const std::initializer_list<unsigned char>& initialValues) {
    arraySize = initialValues.size();
    dataArray = new unsigned char[arraySize];
    size_t index {0};
    for (const auto& value : initialValues) {
        if (value != 0 && value != 1) {
            throw std::invalid_argument("Битовая строка может сотстоять только из 0 или 1");
        }
        dataArray[index++] = value;
    }
}

// конструктор из строки
BitString::BitString(const std::string& sourceString) {
    arraySize = sourceString.size();
    dataArray = new unsigned char[arraySize];
    for (size_t i {0}; i  < arraySize; ++i) {
        if (sourceString[i] != '0' && sourceString[i] != '1') {
            throw std::invalid_argument("Битовая строка может сотстоять только из 0 или 1");
        }
        dataArray[i] = static_cast<unsigned char>(sourceString[i]) - '0';
    }
}

// копирующий
BitString::BitString(const BitString& other)  {
    arraySize = other.arraySize;
    dataArray = new unsigned char[arraySize];

    for (size_t i {0}; i < arraySize; ++i) {
        dataArray[i] = other.dataArray[i];
    }
}

// перемещающий
BitString::BitString(BitString&& other) noexcept {
    arraySize = other.arraySize;
    dataArray = other.dataArray;

    other.arraySize = 0;
    other.dataArray = nullptr;
}

// деструктор
BitString::~BitString() noexcept {
    // std::cout << "Деструктор" << std::endl;
    if (dataArray != nullptr) {
        delete[] dataArray;
        dataArray = nullptr;
    }
    arraySize = 0;
}

void BitString::rm_leading_zeros() {
    if (arraySize == 0) {
        return;
    }
    size_t i {0};
    while (i < arraySize - 1 && dataArray[i] == 0) {
        i++;
    }
    if (i == 0) {
        return;
    }
    size_t new_size = arraySize - i;
    unsigned char* new_data = new unsigned char[new_size];
    for (size_t j {0}; j < new_size; ++j) {
        new_data[j] = dataArray[i + j];
    }
    delete[] dataArray;
    dataArray = new_data;
    arraySize = new_size;
}

unsigned char BitString::last_bit(size_t p) const {
    if (arraySize > p ) {
        return dataArray[arraySize - p - 1];
    } 
    return 0;
}

// компаратор
int BitString::compare(const BitString &other) const {
    BitString copy(*this);
    BitString other_copy(other);
    copy.rm_leading_zeros();
    other_copy.rm_leading_zeros();
    if (copy.arraySize != other_copy.arraySize) {
        return (copy.arraySize > other_copy.arraySize) ? 1 : -1;
    }
    for (size_t i {0}; i < copy.arraySize; ++i) {
        if (copy.dataArray[i] > other_copy.dataArray[i]) return 1;
        if (copy.dataArray[i] < other_copy.dataArray[i]) return -1;
    }
    return 0;
}

double BitString::convert_to_decimal() const {
    int decimal_num {0};
    for (size_t i {0}; i < arraySize; ++i) {
        decimal_num += dataArray[i] * pow(2, arraySize - i - 1);
    } 
    return decimal_num;
}

BitString BitString::add(const BitString& other) {
    size_t max_size = MAX(arraySize, other.arraySize);
    BitString result(max_size + 1, 0);
    int in_the_mind {0};
    for (size_t i {0}; i < max_size; ++i) {
        unsigned char b1 = last_bit(i);
        unsigned char b2 = other.last_bit(i);
        result.dataArray[result.arraySize - i - 1] = (b1 + b2 + in_the_mind) % 2;
        in_the_mind  = (b1 + b2 + in_the_mind) / 2;
    }
    if (in_the_mind) {
        result.dataArray[0] = in_the_mind;
    }
    result.rm_leading_zeros();
    return result;
}

BitString BitString::remove(const BitString &other) {
    if (less(other)) {
        throw std::invalid_argument("Первое число меньше второго");
    }
    BitString result(arraySize, 0);
    int debt {0};
    for (size_t i {0}; i < arraySize; ++i) {
        unsigned char b1 = last_bit(i);
        unsigned char b2 = other.last_bit(i);
        int temp = b1 - b2 - debt;
        if (temp < 0) {
            temp += 2; 
            debt = 1;
        } else {
            debt = 0;
        }
        result.dataArray[arraySize - i - 1] = static_cast<unsigned char>(temp);
    }
    result.rm_leading_zeros();
    return result;
}

BitString BitString::copy() {
    return BitString(*this);
}

bool BitString::more(const BitString &other) {
    return compare(other) == 1;
}

bool BitString::less(const BitString &other) {
    return compare(other) == -1;
}

bool BitString::equally(const BitString &other) {
    return compare(other) == 0;
}

// Операция +=
BitString BitString::oper1(const BitString &other) {
    BitString temp(this->add(other)); 
    if (arraySize != temp.arraySize) {
        delete [] dataArray;
        dataArray = new unsigned char[temp.arraySize];
        arraySize = temp.arraySize;
    }
    for (size_t i {0}; i < arraySize; ++i) {
        dataArray[i] = temp.dataArray[i];
    }
    return *this;
}


// Операция -=
BitString BitString::oper2(const BitString &other) {
    BitString temp(this->remove(other)); 
    if (arraySize != temp.arraySize) {
        delete [] dataArray;
        dataArray = new unsigned char[temp.arraySize];
        arraySize = temp.arraySize;
    }
    for (size_t i {0}; i < arraySize; ++i) {
        dataArray[i] = temp.dataArray[i];
    }
    return *this;
}

BitString BitString::AND(const BitString& other) {
    size_t max_size = MAX(arraySize, other.arraySize);
    BitString result(max_size, 0);
    for (size_t i {0}; i < max_size; ++i) {
        unsigned char b1 = last_bit(i);
        unsigned char b2 = other.last_bit(i);
        result.dataArray[max_size - i - 1] = b1 & b2;
    }
    return result;
}

BitString BitString::OR(const BitString& other) {
    size_t max_size = MAX(arraySize, other.arraySize);
    BitString result(max_size, 0);
    for (size_t i {0}; i < max_size; ++i) {
        unsigned char b1 = last_bit(i);
        unsigned char b2 = other.last_bit(i);
        result.dataArray[max_size - i - 1] = b1 | b2;
    }
    return result;
}

BitString BitString::XOR(const BitString& other) {
    size_t max_size = MAX(arraySize, other.arraySize);
    if (max_size == 0) {
        return BitString(1, 1);
    }
    BitString result(max_size, 0);
    for (size_t i {0}; i < max_size; ++i) {
        unsigned char b1 = last_bit(i);
        unsigned char b2 = other.last_bit(i);
        result.dataArray[max_size - i - 1] = b1 ^ b2;
    }
    return result;
}

BitString BitString::NOT() {
    BitString result(arraySize, 0);
    for (size_t i {0}; i < arraySize; ++i) {
        result.dataArray[i] = dataArray[i] ^ 1;
    }
    return result;
}

std::ostream& BitString::print(std::ostream& outputStream) {
    for (size_t i {0}; i < arraySize; ++i) {
        outputStream << static_cast<int>(dataArray[i]);
    }
    return outputStream;
}
