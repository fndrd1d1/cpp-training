#include <iostream>
#include <cstdint>

/*
    Member initialization list order problem
*/

class First
{
public:
    First() { std::cout << "init First\n"; }
    void f() { std::cout << "use First\n"; }
};

class Second
{
public:
    Second(First& first) {first.f();}
};

class Use
{
public:
    Use()
    : f()       // the order in the member initialization is different than in declaration
    , s(f) {}
private:
    Second s;
    First f;
};

int main()
{
    Use u;
    // Output : use First -> init First
    // BUG!

    /*
        Compiler output:
        4.1.cpp:25:7: warning: field 'f' will be initialized after field 's' [-Wreorder]
        : f()       // the order in the member initialization is different than in declaration
        ^
        1 warning generated.
    */

    // To fix it: fix the order of the member initialization
}