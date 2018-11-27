#include <iostream>

using namespace std;

enum class Style
{
    FLY,
    JUMP
};

class Hero
{
public:
    Hero(Style s)
    : style(s)
    {}

    virtual ~Hero() {}

    virtual void doHeroicStuff()
    {
        cout << "hero mode activated\n";
    }

private:
    Style style;
};

class SuperMan
: public Hero
{
public:
    SuperMan()
    : Hero(Style::FLY)
    {}

    virtual void doHeroicStuff() override
    {
        cout << "SuperMan is super man!\n";
    }
};

void upgradeHero(unique_ptr<Hero> hero, int musclePump)
{
    cout << "hero pumped " << musclePump << "\n";
    hero->doHeroicStuff();
}

int getMusclesForHeros()
{
    return 100;
}

int main()
{
    // don't do this
    // C++ doesn't garuantee in which execution order the parameters
    // are executed.
    // Problem use case:
    // 1. new
    // 2. getMusclesForHeroes
    // 3. unique_ptr constructor
    // if exception happens in 2. than we have a solid memory leak
    upgradeHero(unique_ptr<SuperMan>(new SuperMan()), getMusclesForHeros());

    // do this
    unique_ptr<Hero> clark = make_unique<SuperMan>();
    upgradeHero(move(clark), 10000);

}