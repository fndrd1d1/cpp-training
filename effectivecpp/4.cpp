#include <iostream>

using namespace std;

class MyInt
{
    int i;
public:
    MyInt() : i(0) {}
    MyInt(int j) : i(j) {}
};

class Here
{
public:
    Here()
    {
        // problem:
        // 1. default constructor is called for string and MyInt
        // 2. copy-assignment operator is called
        test = "init";
        len = MyInt(4);
    }

    // better only copy constructor is called
    Here()
    : test("init")
    , len(MyInt(4))
    {}

private:
    string test;
    MyInt len;
};

int main()
{
    Here h();
}