#include <iostream>
#include <string>
#include <vector>

class Hero
{
public:
    void doHeroicStuff() const
    {
        std::cout << "Hero: do it\n";
    }
};

class HeroCollection
{
public:
    void addHero(const Hero& h)
    {
        heroes.push_back(h);
    }
    void groupHeroics()
    {
        for (const Hero& h : heroes)
        {
            h.doHeroicStuff();
        }
    }
    // should not be part of this class
    // violates single responsibilty principle
    void save()
    {
        for (const Hero& h : heroes)
        {
            std::cout << "hero saved\n";
        }
    }
private:
    std::vector<Hero> heroes;
};

// move save to own class according to single responsibility principle
class HeroSaver
{
public:
    static void saveHero(const Hero& h)
    {
        std::cout << "hero saved\n";
    }
};

int main()
{
    HeroCollection hc;
    Hero h1;
    Hero h2;
    hc.addHero(h1);
    hc.addHero(h2);

    hc.groupHeroics();

    HeroSaver::saveHero(h1);
    HeroSaver::saveHero(h2);
}