#include <iostream>
#include <string>

using namespace std;

class var {
private:
    enum Type { INT, DOUBLE, STRING };
    Type dataType;
    union Data {
        int intValue;
        double doubleValue;
        std::string* stringValue;

        // Default constructor for union
        Data() : intValue(0) {}
    } data;

public:
    // Constructors
    var() : dataType(INT), data() {}
    var(int value) : dataType(INT) { data.intValue = value; }
    var(double value) : dataType(DOUBLE) { data.doubleValue = value; }
    var(const std::string& value) : dataType(STRING) {
        data.stringValue = new std::string(value);
    }

    // Destructor
    ~var() {
        if (dataType == STRING) {
            delete data.stringValue;
        }
    }

    // Show method to display the value
    void Show() const;

    // Conversion operators
    operator int() const;
    operator double() const;
    operator const char* () const;

    // Overloading arithmetic operators
    var operator+(const var& other) const;
    var operator-(const var& other) const;
    var operator*(const var& other) const;
    var operator/(const var& other) const;

    // Overloading compound assignment operators
    var& operator+=(const var& other);
    var& operator-=(const var& other);
    var& operator*=(const var& other);
    var& operator/=(const var& other);

    // Overloading comparison operators
    bool operator<(const var& other) const;
    bool operator>(const var& other) const;
    bool operator<=(const var& other) const;
    bool operator>=(const var& other) const;
    bool operator==(const var& other) const;
    bool operator!=(const var& other) const;
};

// Show method to display the value
void var::Show() const {
    switch (dataType) {
    case INT:
        std::cout << data.intValue;
        break;
    case DOUBLE:
        std::cout << data.doubleValue;
        break;
    case STRING:
        std::cout << *data.stringValue;
        break;
    }
    std::cout << std::endl;
}

// Conversion operators
var::operator int() const {
    return data.intValue;
}

var::operator double() const {
    return data.doubleValue;
}

var::operator const char* () const {
    if (dataType == STRING) {
        return data.stringValue->c_str();
    }
    return "Invalid Conversion";
}

// Overloading arithmetic operators
var var::operator+(const var& other) const {
    return (dataType == STRING || other.dataType == STRING) ? (static_cast<double>(*this) + std::stod(static_cast<const char*>(other))) :
        (dataType == DOUBLE || other.dataType == DOUBLE) ? (static_cast<double>(*this) + static_cast<double>(other)) :
        (data.intValue + other.data.intValue);
}

// Conversion operators
var::operator int() const {
    return (dataType == INT) ? data.intValue : static_cast<int>(data.doubleValue);
}

var::operator double() const {
    return (dataType == DOUBLE) ? data.doubleValue : static_cast<double>(data.intValue);
}

var::operator const char*() const {
    if (dataType == STRING) {
        std::string result = *data.stringValue;
        char* cstr = new char[result.length() + 1];
        strcpy(cstr, result.c_str());
        return cstr;
    }
    return "Invalid Conversion";
}

// Repeat the similar implementation for other comparison operators...

int main() {
    int choice;
    std::cout << "Choose the type of variable:\n"
        << "1. Integer\n"
        << "2. Double\n"
        << "3. String\n";
    std::cin >> choice;

    if (choice == 1) {
        int value;
        std::cout << "Enter an integer value: ";
        std::cin >> value;
        var a(value);
        a.Show();
    }
    else if (choice == 2) {
        double value;
        std::cout << "Enter a double value: ";
        std::cin >> value;
        var a(value);
        a.Show();
    }
    else if (choice == 3) {
        std::string value;
        std::cout << "Enter a string value: ";
        std::cin >> value;
        var a(value);
        a.Show();
    }
    else {
        std::cerr << "Invalid choice!" << std::endl;
        return 1;
    }

    return 0;
}
