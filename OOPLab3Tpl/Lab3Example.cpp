#include <iostream>

class Vector {
private:
    long* data;
    int size;
    int& state; // Посилання на int для відстеження стану

public:
    static int numObjects; // Статична змінна для підрахунку кількості об’єктів

    // Конструктори 
    Vector() : data(nullptr), size(0), state(state_), state_(0) {
        ++numObjects;
    }

    Vector(int s) : data(new long[s]), size(s), state(state_), state_(0) {
        ++numObjects;
        for (int i = 0; i < size; ++i)
            data[i] = 0;
    }

    Vector(int s, long value) : data(new long[s]), size(s), state(state_), state_(0) {
        ++numObjects;
        for (int i = 0; i < size; ++i)
            data[i] = value;
    }

    Vector(const Vector& other) : data(new long[other.size]), size(other.size), state(state_), state_(other.state) {
        ++numObjects;
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }

    // Оператор присвоювання
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            data = new long[other.size];
            size = other.size;
            state_ = other.state;
            for (int i = 0; i < size; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    // Destructor
    ~Vector() {
        delete[] data;
        --numObjects;
    }

    // Установлюєм елемент за індексом у значення
    void setElement(int index, long value = 0) {
        if (index >= 0 && index < size) {
            data[index] = value;
            state_ = 0; // Reset state after successful operation
        }
        else {
            state_ = 1; // Index out of bounds
        }
    }

    // Отримати елемент за індексом
    long getElement(int index) {
        if (index >= 0 && index < size) {
            state_ = 0; // Reset state after successful operation
            return data[index];
        }
        else {
            state_ = 1; // Index out of bounds
            return 0; // Return default value
        }
    }

    // Вивід елементів вектора
    void print() {
        for (int i = 0; i < size; ++i)
            std::cout << data[i] << " ";
        std::cout << std::endl;
    }

    // Вектор додавання
    Vector operator+(const Vector& other) {
        Vector result(std::max(size, other.size), 0);
        for (int i = 0; i < std::min(size, other.size); ++i)
            result.data[i] = data[i] + other.data[i];
        return result;
    }

    // Векторне віднімання
    Vector operator-(const Vector& other) {
        Vector result(std::max(size, other.size), 0);
        for (int i = 0; i < std::min(size, other.size); ++i)
            result.data[i] = data[i] - other.data[i];
        return result;
    }

    // Множення вектора на unsigned int
    Vector operator*(unsigned int scalar) {
        Vector result(size, 0);
        for (int i = 0; i < size; ++i)
            result.data[i] = data[i] * scalar;
        return result;
    }

    bool operator<(const Vector& other) {
        return size < other.size;
    }

    bool operator!=(const Vector& other) {
        if (size != other.size)
            return true;
        for (int i = 0; i < size; ++i) {
            if (data[i] != other.data[i])
                return true;
        }
        return false;
    }

    bool operator==(const Vector& other) {
        return !(*this != other);
    }

    // Функція доступу до стану
    int getState() const {
        return state_;
    }

    // Функція доступу до розміру
    int getSize() const {
        return size;
    }

    // Статична функція для отримання кількості об’єктів
    static int getNumObjects() {
        return numObjects;
    }

private:
    int state_; // Змінна стану для відстеження помилок
};

// Ініціалізація статичного член поза визначенням класу
int Vector::numObjects = 0;

int main() {
    int size;
    std::cout << "Enter the size for vector v1: ";
    std::cin >> size;
    Vector v1(size); // Конструктор з параметром size
    std::cout << "Enter " << size << " elements for vector v1: ";
    for (int i = 0; i < size; ++i) {
        long value;
        std::cin >> value;
        v1.setElement(i, value);
    }

    std::cout << "Vector v1: ";
    v1.print();


    std::cout << "Number of Vector objects created: " << Vector::getNumObjects() << std::endl;

    return 0;
}
