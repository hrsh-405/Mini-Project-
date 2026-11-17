// Shape Area Calculator - OOPS Lab Mini Project (CIC-211)
// Group I10: Harsh Sharma, Bhavya Dobliyal
#include <iostream>
#include <iomanip>
#include <limits>
#include <memory>
#include <string>
#include <vector>
using namespace std;

const double PI = 3.14159265358979;

// ---------- Abstract base class ----------
class Shape {
protected:
    string name;
public:
    Shape(const string& n) : name(n) {}
    virtual double area() const = 0;              // pure virtual: each shape overrides it
    virtual void display() const {                // common output, uses runtime polymorphism
        cout << fixed << setprecision(2)
             << name << " -> Area = " << area() << " sq. units\n";
    }
    virtual ~Shape() {}                           // virtual destructor
};

// ---------- Derived classes ----------
class Circle : public Shape {
    double radius;
public:
    Circle(double r) : Shape("Circle"), radius(r) {}
    double area() const override { return PI * radius * radius; }
};

class Rectangle : public Shape {
    double length, breadth;
public:
    Rectangle(double l, double b) : Shape("Rectangle"), length(l), breadth(b) {}
    double area() const override { return length * breadth; }
};

class Triangle : public Shape {
    double base, height;
public:
    Triangle(double b, double h) : Shape("Triangle"), base(b), height(h) {}
    double area() const override { return 0.5 * base * height; }
};

// ---------- Input helper: accepts only valid (positive) numbers ----------
double readPositive(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value > 0) return value;
        cout << "Invalid input! Please enter a number greater than 0.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    vector<unique_ptr<Shape>> history;   // base-class pointers -> runtime polymorphism
    int choice;

    do {
        cout << "\n===== SHAPE AREA CALCULATOR =====\n"
             << "1. Circle\n2. Rectangle\n3. Triangle\n"
             << "4. Show all calculated shapes\n5. Exit\nEnter choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }

        Shape* s = nullptr;                 // base-class pointer
        switch (choice) {
            case 1: s = new Circle(readPositive("Enter radius: ")); break;
            case 2: {
                double l = readPositive("Enter length: ");
                double b = readPositive("Enter breadth: ");
                s = new Rectangle(l, b); break;
            }
            case 3: {
                double b = readPositive("Enter base: ");
                double h = readPositive("Enter height: ");
                s = new Triangle(b, h); break;
            }
            case 4:
                if (history.empty()) cout << "No shapes calculated yet.\n";
                for (const auto& sh : history) sh->display();   // virtual call
                break;
            case 5: cout << "Thank you!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

        if (s) {
            s->display();                   // calls the derived class's area()
            history.emplace_back(s);
        }
    } while (choice != 5);

    return 0;
}
