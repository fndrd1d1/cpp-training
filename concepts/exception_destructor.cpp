#include <iostream>
#include <string>

using namespace std;

class Dog
{
    string name;
    bool cleaned;
public:
    Dog(string n)
    : name(n)
    , cleaned(false)
    {
        cout << "Dog " << name << " created\n";
    }

    ~Dog()
    {
        // throw 20;
        // don't throw exception in destructor

        // Solution:
        try {
            if(!cleaned)
            {
                clean();
            }
            cout << "Dog " << name << " destroyed\n";
        }
        catch (...) // catches all exceptions
        {
            // make log entry
        }
    }

    void bark()
    {
        cout << name << "\n";
    }

    // part of solution
    // introduce separate interface to clean/close
    // user is responsible to call it
    // if it wasn't called destructor will do it but swallow all exceptions
    void clean()
    {
        cout << "clean\n";
        cleaned = true;
    }
};

int main()
{
    try
    {
        Dog dog1("Hund");
        Dog dog2("Schwein"); // destroyed first
        throw 20; // all stack variables will be destroyed before the exception

        dog1.bark();
        dog2.bark();
    }
    catch (int e)
    {
        cout << e << "\n";
    }
}