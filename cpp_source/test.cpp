#include <iostream>
#include <cstdio>

// g++ -o test test.cpp

using namespace std;

class Base
{
public:
    void func()
    {
        cout << "Base func" << endl;
    }

    void func(int a, int b)
    {
        cout << "[int] a + b = " << a + b << endl;
    }

    void func(double a, double b)
    {
        cout << "[double] a + b = " << a + b << endl;
    }
};

class Derived : public Base
{
public:
    void func()
    {
        cout << "Derived func" << endl;
    }
};

int main(int argc, char** argv)
{
    std::cout << "Hello world" << std::endl;
    printf("Hello world\n");
    Base a;
    Derived b;

    cout << "\n[overload 예제]" << endl;

    a.func(1, 2);
    a.func(2.0, 3.3);

    cout << "\n[override 예제]" << endl;

    a.func();
    b.func();

    return 0;
}