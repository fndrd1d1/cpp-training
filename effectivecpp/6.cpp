#include <iostream>

using namespace std;

class Uncopyable {

protected:
    Uncopyable() {}
    ~Uncopyable() {}
private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);

};

class Home
{
public:
    Home() {}
private:
    Home(const Home&);
    Home& operator=(const Home&);
};

class BetterHome
: private Uncopyable
{
    // works same way as Home, but will provide compile time errors
    // It works because the generated copy ctr and copy assignment will
    // call it's base class copy ctor and copy assignment and they are private
};

int main()
{
    Home h;

    // copy ctor not possible since it's private declared
    // Home h2(h);

    // copy assignemnt is not possible since it's private declared
    // Home h2 = h;

    BetterHome bh;
}
