#include <iostream>
#include <string>
#include <vector>

template <typename T>
class Specification
{
  public:
    virtual ~Specification() {};
    virtual bool isSatisfied(const T &item) = 0;
};

template <typename T>
class Filter
{
  public:
    virtual ~Filter() {};
    virtual std::unique_ptr<std::vector<T>> filter(std::vector<T> &items, Specification<T> &spec) = 0;
};

enum class Strength
{
    NOOB,
    NORMAL,
    INSANE
};

class Hero
{
  public:
    explicit Hero(Strength str, std::string name) : _str(str), _name(name)
    {}

    Strength getStrength() const { return _str; }
    std::string getName() const { return _name; }

  private:
    Strength _str;
    std::string _name;
};

class FilterHero
: public Filter<Hero>
{
public:
    std::unique_ptr<std::vector<Hero>> filter(std::vector<Hero> &items, Specification<Hero> &spec) override
    {
        std::unique_ptr<std::vector<Hero>> hv = std::make_unique<std::vector<Hero>>();

        for (auto& h : items)
        {
            if (spec.isSatisfied(h))
            {
                hv->push_back(h);
            }
        }

        return std::move(hv);
    }
};

class StrengthSpecification
: public Specification<Hero>
{
  public:
    explicit StrengthSpecification(Strength str) : _str(str)
    {
    }
    bool isSatisfied(const Hero& item) override
    {
        return item.getStrength() == _str;
    }
  private:
    Strength _str;
};

int main()
{
    std::vector<Hero> v = {Hero(Strength::INSANE, "Superman"), Hero(Strength::NORMAL, "Batman")};
    StrengthSpecification strSpec(Strength::INSANE);
    FilterHero fh;
    auto insane_heroes = fh.filter(v, strSpec);

    std::cout << "insane heroes:\n";
    for (const auto& h : (*insane_heroes))
    {
        std::cout << h.getName() << ", strength = " << static_cast<std::underlying_type<Strength>::type>(h.getStrength()) << '\n';
    }
}