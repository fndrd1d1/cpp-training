#include <iostream>

using namespace std;

class Base
{
public:
    virtual void display() const
    {
        cout << "base display" << endl;
    }
};

class Derived
: public Base
{
public:
    virtual void display() const
    {
        cout << "derived display" << endl;
    }
};

// slicing problem of a happens here
// a is will be treated as Base type
// copy constructor leads to a new object
// all derived object features are sliced off
void print(Base a)
{
    a.display();
}

// const & avoids the slicing problem
// since it uses a pointer to a existing object
void printNoSlicing(const Base& a)
{
    a.display();
}

int main()
{
    Derived a;
    print(a);
    printNoSlicing(a);
}
