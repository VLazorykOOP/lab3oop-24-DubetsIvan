#include <iostream>

class Vector {
private:
    long* data;
    int size;
    int& state;

public:
    static int numObjects;

    Vector() : data(new long[1]), size(1), state(state_), state_(0) {
        ++numObjects;
        data[0] = 0;
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

    ~Vector() {
        delete[] data;
        --numObjects;
    }

    void setElement(int index, long value = 0) {
        if (index >= 0 && index < size) {
            data[index] = value;
            state_ = 0; 
        }
        else {
            state_ = 1; // Index out of bounds
        }
    }

    long getElement(int index) {
        if (index >= 0 && index < size) {
            state_ = 0; // Reset state after successful operation
            return data[index];
        }
        else {
            state_ = 1; 
            return 0; 
        }
    }

    void print() {
        for (int i = 0; i < size; ++i)
            std::cout << data[i] << " ";
        std::cout << std::endl;
    }

    Vector operator+(const Vector& other) {
        Vector result(std::max(size, other.size), 0);
        for (int i = 0; i < std::min(size, other.size); ++i)
            result.data[i] = data[i] + other.data[i];
        return result;
    }

    Vector operator-(const Vector& other) {
        Vector result(std::max(size, other.size), 0);
        for (int i = 0; i < std::min(size, other.size); ++i)
            result.data[i] = data[i] - other.data[i];
        return result;
    }

    
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

    
    int getState() const {
        return state_;
    }

    
    int getSize() const {
        return size;
    }

    
    static int getNumObjects() {
        return numObjects;
    }

private:
    int state_; // State variable for error tracking
};


int Vector::numObjects = 0;

int main() {
    Vector v1; 
    std::cout << "Vector v1: ";
    v1.print();

    Vector v2(5); 
    std::cout << "Vector v2: ";
    v2.print();

    Vector v3(3, 10); 
    std::cout << "Vector v3: ";
    v3.print();

    Vector v4 = v3; 
    std::cout << "Vector v4 (copy of v3): ";
    v4.print();

    Vector v5;
    v5 = v2; 
    std::cout << "Vector v5 (assigned v2): ";
    v5.print();

    
    v2.setElement(2, 7);
    std::cout << "Element at index 2 in v2: " << v2.getElement(2) << std::endl;

    
    Vector v6 = v3 + v4;
    std::cout << "Vector v6 (v3 + v4): ";
    v6.print();

    Vector v7 = v3 - v4;
    std::cout << "Vector v7 (v3 - v4): ";
    v7.print();

    Vector v8 = v3 * 3;
    std::cout << "Vector v8 (v3 * 3): ";
    v8.print();

    
    std::cout << "Is v2 less than v3? " << (v2 < v3) << std::endl;
    std::cout << "Are v3 and v4 equal? " << (v3 == v4) << std::endl;
    std::cout << "Are v3 and v5 not equal? " << (v3 != v5) << std::endl;

    
    v2.setElement(10); // This will set the state to indicate index out of bounds
    std::cout << "State of v2 after setting element at index 10: " << v2.getState() << std::endl;

    std::cout << "Number of Vector objects created: " << Vector::getNumObjects() << std::endl;

    return 0;
}
