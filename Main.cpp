#include <iostream>

class Array {
private:
    int* data;
    int size;

public:
    // ����������� �����
    Array(int sz) : size(sz) {
        data = new int[size];
    }

    // ���������� �����
    ~Array() {
        delete[] data;
    }

    // �������������� ��������� []
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            // ����� �������� ������� ��� �������� ������� ����� �����
            std::cerr << "������������ ������!" << std::endl;
            // ����� ����� ��������� ������ ����������� �������� �� ����� �������
            // ��� ��������� exit(1) ��� ���������� ��������
            exit(1);
        }
        return data[index];
    }

    // �������������� ��������� ()
    void operator()(int valueToAdd) {
        for (int i = 0; i < size; ++i) {
            data[i] += valueToAdd;
        }
    }

    // ������������ �� int
    operator int() const {
        int sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += data[i];
        }
        return sum;
    }

    // ������������ �� char*
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
    // ������� ������������ ����� Array
    Array arr(5);

    // ���������� �����
    for (int i = 0; i < 5; ++i) {
        arr[i] = i + 1;
    }

    // �������� �������� ������ ����� []
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // �������� �� �������� ������ ����� ()
    arr(10);

    // �������� �������� ������ ���� ���������
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // ������������ �� int (���� ��������)
    int sum = arr;
    std::cout << "The sum of array elements: " << sum << std::endl;

    // ������������ �� char* (�������� � ������ �����)
    const char* str = arr;
    std::cout << "Elements of the array in the form of a string: " << str << std::endl;

    return 0;
}
