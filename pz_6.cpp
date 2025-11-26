#include <stdexcept>
#include <iostream>
#include <string>

class MyArray {
private:
    int* data;
    size_t size;

    bool isValidValue(int value) const {
        return value >= -100 && value <= 100;
    }

    bool isValidIndex(size_t index) const {
        return index < size;
    }

public:
    MyArray(size_t arrSize) : size(arrSize) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = 0;
        }
    }

    ~MyArray() {
        delete[] data;
    }

    MyArray(const MyArray& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            if (!isValidValue(other.data[i])) {
                delete[] data;
                throw std::invalid_argument("Copied value " + std::to_string(other.data[i]) + 
                                          " is outside valid range [-100, 100]");
            }
            data[i] = other.data[i];
        }
    }

    MyArray& operator=(const MyArray& other) {
        if (this != &other) {
            // Checking the values before assigning
            for (size_t i = 0; i < other.size; ++i) {
                if (!isValidValue(other.data[i])) {
                    throw std::invalid_argument("Assigned value " + std::to_string(other.data[i]) + 
                                              " is outside valid range [-100, 100]");
                }
            }
            
            delete[] data;
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    int& operator[](size_t index) {
        if (!isValidIndex(index)) {
            throw std::out_of_range("Index " + std::to_string(index) + 
                                  " is out of range for array of size " + 
                                  std::to_string(size));
        }
        return data[index];
    }

    const int& operator[](size_t index) const {
        if (!isValidIndex(index)) {
            throw std::out_of_range("Index " + std::to_string(index) + 
                                  " is out of range for array of size " + 
                                  std::to_string(size));
        }
        return data[index];
    }

    void setValue(size_t index, int value) {
        if (!isValidIndex(index)) {
            throw std::out_of_range("Index " + std::to_string(index) + 
                                  " is out of range for array of size " + 
                                  std::to_string(size));
        }
        if (!isValidValue(value)) {
            throw std::invalid_argument("Value " + std::to_string(value) + 
                                      " is outside valid range [-100, 100]");
        }
        data[index] = value;
    }

    size_t getSize() const {
        return size;
    }

    void print() const {
        std::cout << "[";
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i];
            if (i < size - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
};

// Usage example
int main() {
    try {
        MyArray arr(5);
        
        // Correct operations
        arr.setValue(0, 10);
        arr.setValue(1, -50);
        arr.setValue(2, 100);
        arr.print();
        
        // Attempt to set an invalid value
        arr.setValue(3, 150);
        
    } catch (const std::out_of_range& e) {
        std::cout << "Range error: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Argument error: " << e.what() << std::endl;
    }

    try {
        MyArray arr(3);
        
        // Attempting to access a non-existent index
        int value = arr[5];
        
    } catch (const std::out_of_range& e) {
        std::cout << "Range error: " << e.what() << std::endl;
    }

    return 0;
}