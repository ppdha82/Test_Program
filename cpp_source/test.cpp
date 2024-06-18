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

    virtual void vfunc1()
    {
        cout << "virtual base" << __func__ << endl;
    }

    virtual void vfunc2()
    {
        cout << "virtual base" << __func__ << endl;
    }

    void vfunc3()
    {
        cout << "virtual base" << __func__ << endl;
    }

    void vfunc4()
    {
        cout << "virtual base" << __func__ << endl;
    }
};

class Derived : public Base
{
public:
    void func()
    {
        cout << "Derived func" << endl;
    }

    virtual void vfunc1()
    {
        cout << "virtual derived" << __func__ << endl;
    }

    void vfunc2()
    {
        cout << "virtual derived" << __func__ << endl;
    }

    virtual void vfunc3()
    {
        cout << "virtual derived" << __func__ << endl;
    }

    void vfunc4()
    {
        cout << "virtual derived" << __func__ << endl;
    }
};

int main(int argc, char** argv)
{
    cout << "Hello world" << std::endl;
    printf("Hello world\n");
    Base a;
    Derived b;
    Base *pA;

    cout << "\n[overload 예제]" << endl;

    a.func(1, 2);
    a.func(2.0, 3.3);

    cout << "\n[override 예제]" << endl;

    a.func();
    b.func();

    cout << "\n[virtual 예제]" << endl;

    pA = &b;
    a.vfunc1();
    pA->vfunc1();

    cout << "\n";

    a.vfunc2();
    pA->vfunc2();

    cout << "\n";

    a.vfunc3();
    pA->vfunc3();

    cout << "\n";

    a.vfunc4();
    pA->vfunc4();

    return 0;
}