#include <iostream>

using namespace std;

class Transaction
{
public:
    Transaction()
    {
        // call of virtual function in base class yields undefined behaviour
        // both methods should be avoided
        // never call a virtual function in a constructor or destructor
        //log();
        //init();

    }
    virtual void log() const = 0;
private:
    void init()
    {
        log();
    }
};

class BetterTransaction
{
public:
    explicit BetterTransaction(const string& info)
    {
        log(info);
    }

    void log(const string& info) const
    {
        cout << info <<"\n";
    }
};

class BuyTransaction
: public Transaction
{
public:
    virtual void log() const
    {
        cout << "log\n";
    }
};

class BetterBuyTransaction
: public BetterTransaction
{
public:
    BetterBuyTransaction()
    : BetterTransaction(createLog("log"))
    {}

private:
static string createLog(const string& test)
{
    return test;
}
};

int main()
{
    BuyTransaction b;
    BetterBuyTransaction b2;
}
