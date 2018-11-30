#include <iostream>

using namespace std;

class Janitor
{
public:
    Janitor(int cp)
    : cleaningPower(cp)
    {}
    void cleanBackyard() const
    {
        cout << "cleaning backyard with power=" << cleaningPower << "\n";
    }
    void cleanFrontyard() const
    {
        cout << "cleaning frontyard with power=" << cleaningPower << "\n";
    }
    // potential problem
    void cleanAll()
    {
        cleanBackyard();
        cleanFrontyard();
    }
private:
    int cleaningPower;
};

// better than internal method
// - provides better encapsulation
//      -> doesn't have access to internals of Janitor
// - provides better packaging flexibility
//      -> can live inside own utility header
// - functional extensibility
void cleanAll(const Janitor& j)
{
    j.cleanBackyard();
    j.cleanFrontyard();
}

int main()
{
    Janitor j(100);
    cleanAll(j);
}