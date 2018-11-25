#include <iostream>

using namespace std;

class Base
{
public:
    Base(){cout << "Base ctor\n";}

    // always use virtual destructor in polymorphic base class
    // else only base class dtor will be called
    virtual ~Base(){cout << "Base dtor\n";}

    virtual void doIt() = 0;
};

class Derived
: public Base
{
public:
    Derived(){cout << "Derived ctor\n";}
    ~Derived(){cout << "Derived dtor\n";}

    virtual void doIt()
    {
        int i = 1;
    }
};

int main()
{
    Base* b = new Derived();

    delete b;

}
