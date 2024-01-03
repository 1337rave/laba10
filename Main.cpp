#include <iostream>

class Array {
private:
    int* data;
    int size;

public:
    // Конструктор класу
    Array(int sz) : size(sz) {
        data = new int[size];
    }

    // Деструктор класу
    ~Array() {
        delete[] data;
    }

    // Перевантаження оператора []
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            // Можна викинути виняток або обробити помилку іншим чином
            std::cerr << "Неправильний індекс!" << std::endl;
            // Можна також повернути якийсь спеціальний значення за умови помилки
            // або викликати exit(1) для завершення програми
            exit(1);
        }
        return data[index];
    }

    // Перевантаження оператора ()
    void operator()(int valueToAdd) {
        for (int i = 0; i < size; ++i) {
            data[i] += valueToAdd;
        }
    }

    // Перетворення до int
    operator int() const {
        int sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += data[i];
        }
        return sum;
    }

    // Перетворення до char*
    operator const char* () const {
        const int bufferSize = size * 3 + 1; // Each element can have at most 3 characters (including space), and 1 for '\0'
        char* result = new char[bufferSize];
        int written = 0;

        for (int i = 0; i < size; ++i) {
            written += sprintf_s(result + written, bufferSize - written, "%d ", data[i]);
        }

        return result;
    }
};

int main() {
    // Приклад використання класу Array
    Array arr(5);

    // Заповнюємо масив
    for (int i = 0; i < 5; ++i) {
        arr[i] = i + 1;
    }

    // Виводимо елементи масиву через []
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Збільшуємо всі елементи масиву через ()
    arr(10);

    // Виводимо елементи масиву після збільшення
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Перетворення до int (сума елементів)
    int sum = arr;
    std::cout << "The sum of array elements: " << sum << std::endl;

    // Перетворення до char* (елементи у вигляді рядка)
    const char* str = arr;
    std::cout << "Elements of the array in the form of a string: " << str << std::endl;

    return 0;
}
