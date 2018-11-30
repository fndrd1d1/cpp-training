#include <iostream>

struct Hero
{
    virtual void doHeroicStuff() { std::cout << "normal hero stuff\n"; }
};

struct Superman : public Hero
{
    virtual void doHeroicStuff() { std::cout << "superman is super man\n"; }
};

struct Batman : public Hero
{
    virtual void doHeroicStuff() { std::cout << "batman is bad man\n"; }
};

int main()
{
    std::unique_ptr<Hero> h1 = std::make_unique<Hero>();
    std::unique_ptr<Hero> h2 = std::make_unique<Superman>();

    Superman* sMan;

    sMan = dynamic_cast<Superman*>(h2.get());
    if (nullptr != sMan)
    {
        sMan->doHeroicStuff();
    }

    // potentially slow
    // needs RTTI to dynamic_cast
    // used for save upcast
    sMan = dynamic_cast<Superman*>(h1.get());
    if (nullptr == sMan)
    {
        std::cout << "runtime check: failed to cast from Hero to Superman\n";
    }

    // no checks at runtime
    // developer is responsible for correct casting
    // used for up/downcast
    sMan = static_cast<Superman*>(h2.get());
    sMan->doHeroicStuff();

    std::unique_ptr<Batman> batMan = std::make_unique<Batman>();

    // can cast unrelated classes
    // reinterprets the byte representation of the type
    // results in not portable code
    sMan = reinterpret_cast<Superman*>(batMan.get());


    // const_cast can cast const away
    const std::unique_ptr<Superman> constHero = std::make_unique<Superman>();
    sMan = const_cast<Superman*>(constHero.get());

}