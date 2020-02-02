#include <iostream>
#include <string>

// Summary of disallowing Functions:
// 1. C++11 : f() = delete
// 2. C++03 : declare private
// 3. private destructor : stay out of stack

using namespace std;

class OpenFile
{
public:
    OpenFile(string name) // constructor
    {
        cout << "Open file " << name << "\n";
    }

    // 2. Goal
    // don't want this to be possible
    // g has access to private methods
    // -> it isn't possible because copy constructor is only declared
    OpenFile g(OpenFile& f)
    {
        OpenFile f2(f);
    }

private:
    // Solution:
    // c++03: make copy constructor private
    // c++1x: = delete;
    OpenFile(OpenFile& other);
    OpenFile& operator=(const OpenFile& other);

    // making destructor private means
    // the object can't be created on the stack,
    // because stack unwinding calls destructors automatically
    // once object is out of scope
    ~OpenFile()
    {
        cout << "destructor\n";
    }
};

int main()
{
    OpenFile f(string("test"));
    OpenFile t(string("t"));
    OpenFile h = f.g(t);

    // 1. Goal
    // don't want this to be possible
    OpenFile f2(f); //call the copy constructor
}