#include "../include/bitstring.h"

BitString::BitString() : arraySize(0), dataArray(nullptr) {}

BitString::BitString(const size_t& arraySize, unsigned char defaultValue) {
    if (defaultValue != 0 && defaultValue != 1) {
        throw std::invalid_argument("Битовая строка может сотстоять только из 0 или 1");
    }
    this->arraySize = arraySize;
    this->dataArray = new unsigned char[arraySize];
    for (size_t i = 0; i < arraySize; ++i) {
        this->dataArray[i] = defaultValue;
    }
}

BitString::BitString(const std::initializer_list<unsigned char>& initialValues) {
    arraySize = initialValues.size();
    dataArray = new unsigned char[arraySize];
    size_t index = 0;
    for (const auto& value : initialValues) {
        if (value != 0 && value != 1) {
            throw std::invalid_argument("Битовая строка может сотстоять только из 0 или 1");
        }
        dataArray[index++] = value;
    }
}

BitString::BitString(const std::string& sourceString) {
    arraySize = sourceString.size();
    dataArray = new unsigned char[arraySize];
    for (size_t i = 0; i  < arraySize; i++) {
        if (sourceString[i] != '0' && sourceString[i] != '1') {
            throw std::invalid_argument("Битовая строка может сотстоять только из 0 или 1");
        }
        dataArray[i] = static_cast<unsigned char>(sourceString[i]) - '0';
    }
}

BitString::BitString(const BitString& other)  {
    arraySize = other.arraySize;
    dataArray = new unsigned char[arraySize];

    for (size_t i = 0; i < arraySize; ++i) {
        dataArray[i] = other.dataArray[i];
    }
}

BitString::BitString(BitString&& other) noexcept {
    arraySize = other.arraySize;
    dataArray = other.dataArray;

    other.arraySize = 0;
    other.dataArray = nullptr;
}

BitString::~BitString() noexcept {
    std::cout << "Деструктор" << std::endl;
    if (dataArray != nullptr) {
        delete[] dataArray;
        dataArray = nullptr;
    }
    arraySize = 0;
}

void BitString::removing_leading_zeros() {
    size_t i = 0;
    while (i < arraySize - 1 && dataArray[i] == 0) {
        i++;
    }
    if (i == 0) return; 
    size_t newSize = arraySize - i;
    unsigned char* newData = new unsigned char[newSize];
    for (size_t j = 0; j < newSize; j++) {
        newData[j] = dataArray[i + j];
    }
    delete[] dataArray;
    dataArray = newData;
    arraySize = newSize;
}

BitString BitString::add(const BitString& other) {
    size_t maxSize = std::max(arraySize, other.arraySize);
    BitString result(maxSize + 1, 0);
    unsigned char carry = 0;
    for (int i = 0; i < maxSize; i++) {
        int idx1 = arraySize - 1 - i;
        int idx2 = other.arraySize - 1 - i;
        int idxResult = result.arraySize - 1 - i;
            
        unsigned char bit1 = (idx1 >= 0) ? dataArray[idx1] : 0;
        unsigned char bit2 = (idx2 >= 0) ? other.dataArray[idx2] : 0;
                
        unsigned char sum = bit1 + bit2 + carry;
        result.dataArray[idxResult] = sum % 2;
        carry = sum / 2;
    }
    if (carry > 0) {
        result.dataArray[0] = carry;
    } 

    result.removing_leading_zeros();
   
    return result;
}

BitString BitString::remove(const BitString &other) {
    BitString result(arraySize, 0);
    int borrow = 0;
    
    for (int i = 0; i < arraySize; i++) {
        int idx1 = arraySize - 1 - i;
        int idx2 = other.arraySize - 1 - i;
        
        int bit1 = dataArray[idx1];
        int bit2 = (idx2 >= 0) ? other.dataArray[idx2] : 0;
        
        int diff = bit1 - bit2 - borrow;
        
        if (diff < 0) {
            diff += 2;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.dataArray[idx1] = static_cast<unsigned char>(diff);
    }
    result.removing_leading_zeros();
    return result;
}

BitString BitString::copy() {
    return BitString(*this);
}



bool BitString::more(const BitString &other) {
    int num1 {0}, num2 {0};
    for (size_t i = 0; i < arraySize; ++i) {
        num1 += dataArray[i] * pow(2, arraySize - i - 1);
    } 
    for (size_t i = 0; i < other.arraySize; ++i) {
        num2 += other.dataArray[i] * pow(2, other.arraySize - i - 1);
    } 
    if (num1 > num2) {
        return true;
    }
}

bool BitString::less(const BitString &other) {
    int num1 {0}, num2 {0};
    for (size_t i = 0; i < arraySize; ++i) {
        num1 += dataArray[i] * pow(2, arraySize - i - 1);
    } 
    for (size_t i = 0; i < other.arraySize; ++i) {
        num2 += other.dataArray[i] * pow(2, other.arraySize - i - 1);
    } 
    if (num1 < num2) {
        return true;
    }
    return false;
}

bool BitString::equally(const BitString &other) {
    int num1 {0}, num2 {0};
    for (size_t i = 0; i < arraySize; ++i) {
        num1 += dataArray[i] * pow(2, arraySize - i - 1);
    } 
    for (size_t i = 0; i < other.arraySize; ++i) {
        num2 += other.dataArray[i] * pow(2, other.arraySize - i - 1);
    } 
    if (num1 == num2) {
        return true;
    }
    return false;
}

BitString BitString::oper1(const BitString &other) {
    BitString result(this->add(other)); 
    delete[] dataArray;

    arraySize = result.arraySize;
    dataArray = result.dataArray;
    
    result.arraySize = 0;
    result.dataArray = nullptr;
    
    return *this;
}

BitString BitString::oper2(const BitString &other) {
    BitString result(this->remove(other)); 
    delete[] dataArray;

    arraySize = result.arraySize;
    dataArray = result.dataArray;

    result.arraySize = 0;
    result.dataArray = nullptr;
    
    return *this;
}

BitString BitString::AND(const BitString& other) {
    size_t max_size = (arraySize > other.arraySize) ? arraySize : other.arraySize;
    BitString result(max_size, 0);
    
    for (int i = 0; i < max_size; i++) {
        int idx1 = arraySize - 1 - i;
        int idx2 = other.arraySize - 1 - i;
        
        unsigned char bit1 = (idx1 >= 0) ? dataArray[idx1] : 0;
        unsigned char bit2 = (idx2 >= 0) ? other.dataArray[idx2] : 0;
        result.dataArray[max_size - i - 1] = bit1 & bit2;
    }
    return result;
}

BitString BitString::OR(const BitString& other) {
    size_t max_size = (arraySize > other.arraySize) ? arraySize : other.arraySize;
    BitString result(max_size, 0);
    
    for (int i = 0; i < max_size; i++) {
        int idx1 = arraySize - 1 - i;
        int idx2 = other.arraySize - 1 - i;
        int idxResult = result.arraySize - 1 - i;
        
        unsigned char bit1 = (idx1 >= 0) ? dataArray[idx1] : 0;
        unsigned char bit2 = (idx2 >= 0) ? other.dataArray[idx2] : 0;
        result.dataArray[max_size - i - 1] = bit1 | bit2;
    }
    return result;
}

BitString BitString::XOR(const BitString& other) {
    size_t max_size = (arraySize > other.arraySize) ? arraySize : other.arraySize;
    BitString result(max_size, 0);
    
    for (int i = 0; i < max_size; i++) {
        int idx1 = arraySize - 1 - i;
        int idx2 = other.arraySize - 1 - i;
        int idxResult = result.arraySize - 1 - i;
        
        unsigned char bit1 = (idx1 >= 0) ? dataArray[idx1] : 0;
        unsigned char bit2 = (idx2 >= 0) ? other.dataArray[idx2] : 0;
        result.dataArray[max_size - i - 1] = bit1 ^ bit2;
    }
    return result;
}

BitString BitString::NOT(const BitString& num) {
    BitString result(num.arraySize, 0);
    for (size_t i = 0; i < arraySize; ++i) {
        result.dataArray[i] = abs(1- dataArray[i]);
    }
    return result;
}

std::ostream& BitString::print(std::ostream& outputStream) {
    for (size_t i = 0; i < arraySize; ++i) {
        outputStream << static_cast<int>(dataArray[i]);
    }
    return outputStream;
}
