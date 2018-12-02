#include <iostream>
#include <functional>


// template method via NVI (non virtual interface)
// compile time decision
class HeroTemplateMethod
{
public:
    int getHealth()
    {
        // non virtual interface
        // call of a private virtual function inside a non virtual interface
        // allows pre and post processing
        return doGetHealth();
    }
private:
    virtual int doGetHealth()
    {
        return 100;
    }
};

class Superman : public HeroTemplateMethod
{
private:
    virtual int doGetHealth() override
    {
        return 1000;
    }
};

class HeroStrategy;
int defaultHealthFunc(const HeroStrategy&);

// strategy pattern with std::function
// run time decision
// std::function gives big flexibility
// use of any callable entity is possible
class HeroStrategy
{
public:
    typedef std::function<int (const HeroStrategy&)> HeroHealthFunc;

    explicit HeroStrategy(HeroHealthFunc hcf = defaultHealthFunc)
    : healthFunc(hcf)
    {}

    int getHealth()
    {
        return healthFunc(*this);
    }

private:
    HeroHealthFunc healthFunc;
};

int defaultHealthFunc(const HeroStrategy&)
{
    return 100;
}

int main()
{
    std::unique_ptr<HeroTemplateMethod> hSup(new Superman());
    std::cout << "TemplateMethod with child class: " << hSup->getHealth() << '\n';

    HeroStrategy h1;
    std::cout << "Strategy with default function: " << h1.getHealth() << '\n';

    HeroStrategy h2([](const HeroStrategy&) {return 1000;});
    std::cout << "Strategy with lambda: " << h2.getHealth() << '\n';
}