﻿#include <iostream>

class Vector {
private:
    long* data;
    int size;
    int& state; // Using reference to int to track state

public:
    static int numObjects; // Static variable to count the number of objects

    // Constructors
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

    // Copy constructor
    Vector(const Vector& other) : data(new long[other.size]), size(other.size), state(state_), state_(other.state) {
        ++numObjects;
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }

    // Assignment operator
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

    // Set element at index to a value
    void setElement(int index, long value = 0) {
        if (index >= 0 && index < size) {
            data[index] = value;
            state_ = 0; // Reset state after successful operation
        }
        else {
            state_ = 1; // Index out of bounds
        }
    }

    // Get element at index
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

    // Print vector elements
    void print() {
        for (int i = 0; i < size; ++i)
            std::cout << data[i] << " ";
        std::cout << std::endl;
    }

    // Vector addition
    Vector operator+(const Vector& other) {
        Vector result(std::max(size, other.size), 0);
        for (int i = 0; i < std::min(size, other.size); ++i)
            result.data[i] = data[i] + other.data[i];
        return result;
    }

    // Vector subtraction
    Vector operator-(const Vector& other) {
        Vector result(std::max(size, other.size), 0);
        for (int i = 0; i < std::min(size, other.size); ++i)
            result.data[i] = data[i] - other.data[i];
        return result;
    }

    // Vector multiplication by unsigned int
    Vector operator*(unsigned int scalar) {
        Vector result(size, 0);
        for (int i = 0; i < size; ++i)
            result.data[i] = data[i] * scalar;
        return result;
    }

    // Less than comparison
    bool operator<(const Vector& other) {
        return size < other.size;
    }

    // Not equal to comparison
    bool operator!=(const Vector& other) {
        if (size != other.size)
            return true;
        for (int i = 0; i < size; ++i) {
            if (data[i] != other.data[i])
                return true;
        }
        return false;
    }

    // Equal to comparison
    bool operator==(const Vector& other) {
        return !(*this != other);
    }

    // Accessor function for state
    int getState() const {
        return state_;
    }

    // Accessor function for size
    int getSize() const {
        return size;
    }

    // Static function to get number of objects
    static int getNumObjects() {
        return numObjects;
    }

private:
    int state_; // State variable for error tracking
};

// Initialize static member outside the class definition
int Vector::numObjects = 0;

int main() {
    int size;
    std::cout << "Enter the size for vector v1: ";
    std::cin >> size;
    Vector v1(size); // Constructor with size parameter
    std::cout << "Enter " << size << " elements for vector v1: ";
    for (int i = 0; i < size; ++i) {
        long value;
        std::cin >> value;
        v1.setElement(i, value);
    }

    std::cout << "Vector v1: ";
    v1.print();

    // Similarly, input for other vectors can be added here

    std::cout << "Number of Vector objects created: " << Vector::getNumObjects() << std::endl;

    return 0;
}
