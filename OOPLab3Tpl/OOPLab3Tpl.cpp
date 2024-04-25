#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class Triangle {
private:
    double side1, side2, side3;
    string color;

public:
    // Конструктори
    Triangle() : side1(), side2(), side3(), color("black") {}

    Triangle(double s1, double s2, double s3, const string& c) : color(c) {
        setSides(s1, s2, s3);
    }

    // Функції-члени обчислення площі трикутника
    double area() const {
        double s = perimeter() / 2;
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    // Функції-члени обчислення периметру трикутника
    double perimeter() const {
        return side1 + side2 + side3;
    }

    // Функції-члени встановлення значень сторін та кольору
    void setSides(double s1, double s2, double s3) {
        if (isValidTriangle(s1, s2, s3)) {
            side1 = s1;
            side2 = s2;
            side3 = s3;
        }
        else {
            cout << "Invalid sides! Triangle not formed." << endl;
        }
    }

    void setColor(const string& c) {
        color = c;
    }

    // Функції-члени що повертають значення полів
    double getSide1() const {
        return side1;
    }

    double getSide2() const {
        return side2;
    }

    double getSide3() const {
        return side3;
    }

    string getColor() const {
        return color;
    }

    // Функція друку
    void print() const {
        cout << "Triangle with sides: " << side1 << ", " << side2 << ", " << side3 << " and color: " << color << endl;
    }

private:
    // Перевірка чи можна побудувати трикутник з заданими сторонами
    bool isValidTriangle(double s1, double s2, double s3) const {
        return (s1 + s2 > s3) && (s1 + s3 > s2) && (s2 + s3 > s1);
    }
};

int main1() {
    // Трикутник, заданий програмою за замовчуванням
    Triangle defaultTriangle(3, 4, 5, "red");
    cout << "Default Triangle:" << endl;
    defaultTriangle.print();
    cout << "Area: " << defaultTriangle.area() << endl;
    cout << "Perimeter: " << defaultTriangle.perimeter() << endl << endl;

    // Трикутник, введений користувачем
    double side1, side2, side3;
    string color;

    cout << "Enter the sides of the triangle: ";
    cin >> side1 >> side2 >> side3;

    cout << "Enter the color of the triangle: ";
    cin >> color;

    Triangle userTriangle(side1, side2, side3, color);
    cout << "User's Triangle:" << endl;
    userTriangle.print();
    cout << "Area: " << userTriangle.area() << endl;
    cout << "Perimeter: " << userTriangle.perimeter() << endl;

    return 0;
}