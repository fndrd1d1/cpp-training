#include <iostream>

using namespace std;

template <typename T>
class NameObject {
public:
    NameObject(const string& name, const T& value)
    : nameValue(name)
    , objectValue(value)
    {}
private:
    string nameValue;
    T objectValue;
};

template <typename T>
class NameObjectNoDefaultCopy {
public:
    NameObjectNoDefaultCopy(string& name, const T& value)
    : nameValue(name)
    , objectValue(value)
    {}
private:
    string& nameValue;
    const T objectValue;
};

int main()
{
    NameObject<int> n("first", 1);

    // no default ctor will be generated
    // because custom constructor provided
    // NameObject<int> no;

    // Copy ctor generated automatically
    // copys alls non static members to new object
    NameObject<int> n2(n);

    // Copy assignment generated automatically
    // same as copy ctor
    n = n2;

    string f("first");
    string s("second");
    NameObjectNoDefaultCopy<int> ndc(f, 1);
    NameObjectNoDefaultCopy<int> ndc2(s, 2);
    // no default copy assignment can be generated because
    // a class member is a reference
    // ndc = ndc2;
}
