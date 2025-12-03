#include <stdexcept>
#include <iostream>
#include <string>
#include <algorithm>

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
    // Конструктор с размером
    MyArray(size_t arrSize) : size(arrSize) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = 0;
        }
    }

    // Конструктор копирования
    MyArray(const MyArray& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    // Деструктор
    ~MyArray() {
        delete[] data;
    }

    // Оператор присваивания
    MyArray& operator=(const MyArray& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Сеттер с проверкой значения и индекса
    void setValueWithCheck(size_t index, int value) {
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

    // Сеттер с проверкой только индекса
    void setValue(size_t index, int value) {
        if (!isValidIndex(index)) {
            throw std::out_of_range("Index " + std::to_string(index) + 
                                  " is out of range for array of size " + 
                                  std::to_string(size));
        }
        data[index] = value;
    }

    // Геттер
    int getValue(size_t index) const {
        if (!isValidIndex(index)) {
            throw std::out_of_range("Index " + std::to_string(index) + 
                                  " is out of range for array of size " + 
                                  std::to_string(size));
        }
        return data[index];
    }

    // Добавление значения в конец с расширением массива
    void push_back(int value) {
        if (!isValidValue(value)) {
            throw std::invalid_argument("Value " + std::to_string(value) + 
                                      " is outside valid range [-100, 100]");
        }
        
        // Создаем новый массив большего размера
        size_t newSize = size + 1;
        int* newData = new int[newSize];
        
        // Копируем старые данные
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        
        // Добавляем новое значение
        newData[size] = value;
        
        // Освобождаем старую память и обновляем указатель и размер
        delete[] data;
        data = newData;
        size = newSize;
    }

    // Сложение массивов (поэлементное)
    MyArray add(const MyArray& other) const {
        size_t maxSize = std::max(size, other.size);
        MyArray result(maxSize);
        
        for (size_t i = 0; i < maxSize; ++i) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.size) ? other.data[i] : 0;
            int sum = val1 + val2;
            
            // Проверка результата на допустимый диапазон
            if (!isValidValue(sum)) {
                throw std::invalid_argument("Result value " + std::to_string(sum) + 
                                          " is outside valid range [-100, 100]");
            }
            result.data[i] = sum;
        }
        
        return result;
    }

    // Вычитание массивов (поэлементное)
    MyArray subtract(const MyArray& other) const {
        size_t maxSize = std::max(size, other.size);
        MyArray result(maxSize);
        
        for (size_t i = 0; i < maxSize; ++i) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.size) ? other.data[i] : 0;
            int diff = val1 - val2;
            
            // Проверка результата на допустимый диапазон
            if (!isValidValue(diff)) {
                throw std::invalid_argument("Result value " + std::to_string(diff) + 
                                          " is outside valid range [-100, 100]");
            }
            result.data[i] = diff;
        }
        
        return result;
    }

    // Оператор [] для удобства
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

    size_t getSize() const {
        return size;
    }

    // Вывод массива
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

// Пример использования
int main() {
    try {
        // Тестирование базового функционала
        std::cout << "=== Тест 1: Создание и заполнение массива ===" << std::endl;
        MyArray arr1(3);
        
        // Корректные значения
        arr1.setValueWithCheck(0, 10);
        arr1.setValueWithCheck(1, -50);
        arr1.setValueWithCheck(2, 100);
        std::cout << "arr1: ";
        arr1.print();
        
        // Попытка установить некорректное значение
        std::cout << "\nПопытка установить значение 150:" << std::endl;
        arr1.setValueWithCheck(1, 150); // Бросит исключение
        
    } catch (const std::invalid_argument& e) {
        std::cout << "Ошибка аргумента: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Ошибка диапазона: " << e.what() << std::endl;
    }

    try {
        std::cout << "\n=== Тест 2: Конструктор копирования ===" << std::endl;
        MyArray arr2(2);
        arr2.setValueWithCheck(0, 30);
        arr2.setValueWithCheck(1, -70);
        
        MyArray arr3 = arr2; // Конструктор копирования
        std::cout << "arr2: ";
        arr2.print();
        std::cout << "arr3 (копия arr2): ";
        arr3.print();
        
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    try {
        std::cout << "\n=== Тест 3: Добавление элемента в конец ===" << std::endl;
        MyArray arr4(2);
        arr4.setValueWithCheck(0, 20);
        arr4.setValueWithCheck(1, 40);
        std::cout << "arr4 до добавления: ";
        arr4.print();
        
        arr4.push_back(60);
        std::cout << "arr4 после добавления 60: ";
        arr4.print();
        
        // Попытка добавить некорректное значение
        std::cout << "\nПопытка добавить значение 200:" << std::endl;
        arr4.push_back(200); // Бросит исключение
        
    } catch (const std::invalid_argument& e) {
        std::cout << "Ошибка аргумента: " << e.what() << std::endl;
    }

    try {
        std::cout << "\n=== Тест 4: Сложение и вычитание массивов ===" << std::endl;
        MyArray arr5(3);
        arr5.setValueWithCheck(0, 10);
        arr5.setValueWithCheck(1, 20);
        arr5.setValueWithCheck(2, 30);
        
        MyArray arr6(2);
        arr6.setValueWithCheck(0, 5);
        arr6.setValueWithCheck(1, 15);
        
        std::cout << "arr5: ";
        arr5.print();
        std::cout << "arr6: ";
        arr6.print();
        
        // Сложение
        MyArray sum = arr5.add(arr6);
        std::cout << "arr5 + arr6: ";
        sum.print();
        
        // Вычитание
        MyArray diff = arr5.subtract(arr6);
        std::cout << "arr5 - arr6: ";
        diff.print();
        
        // Тест с массивом разного размера
        std::cout << "\n=== Тест 5: Массивы разного размера ===" << std::endl;
        MyArray arr7(1);
        arr7.setValueWithCheck(0, 50);
        
        MyArray arr8(4);
        arr8.setValueWithCheck(0, 10);
        arr8.setValueWithCheck(1, 20);
        arr8.setValueWithCheck(2, 30);
        arr8.setValueWithCheck(3, 40);
        
        std::cout << "arr7: ";
        arr7.print();
        std::cout << "arr8: ";
        arr8.print();
        
        MyArray sum2 = arr7.add(arr8);
        std::cout << "arr7 + arr8: ";
        sum2.print();
        
    } catch (const std::invalid_argument& e) {
        std::cout << "Ошибка аргумента: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Ошибка диапазона: " << e.what() << std::endl;
    }

    try {
        std::cout << "\n=== Тест 6: Обращение по несуществующему индексу ===" << std::endl;
        MyArray arr9(3);
        arr9.setValueWithCheck(0, 10);
        
        // Попытка доступа к несуществующему индексу
        std::cout << "Попытка получить значение по индексу 5:" << std::endl;
        int value = arr9[5]; // Бросит исключение
        
    } catch (const std::out_of_range& e) {
        std::cout << "Ошибка диапазона: " << e.what() << std::endl;
    }

    return 0;
}