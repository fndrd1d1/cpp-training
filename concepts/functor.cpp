#include <iostream>
#include <cstdint>
#include <vector>

// function
template <typename T, T more>
void addFun(T& i)
{
    i+=more;
}

// Add functor
template <typename T>
class Add
{
public:

    Add(T addingValue)
    : more(addingValue)
    {
    }

    void operator()(T& i)
    {
       i += more;
    }
private:
    T more;
};

int main()
{
    std::vector<uint32_t> v = {1, 2, 3, 4, 5};


    std::cout << "function\n";
    /*
     * 10 is a compile time constant
     * Not possible to use a runtime variable
     */
    std::for_each(v.begin(), v.end(), addFun<uint32_t, 10>);

    for(auto a : v)
    {
        std::cout << a << " ";
    }

    std::cout << "\n\nfunctor\n";

    uint32_t dynamicVal = 10;
    /*
     * dynamicVal is a runtime variable
     */
    std::for_each(v.begin(), v.end(), Add<uint32_t>(dynamicVal));

    for(auto a : v)
    {
        std::cout << a << " ";
    }

    std::cout << "\n\nlambda\n";

    /*
     * lambda can also use a runtime variable
     */
    std::for_each(v.begin(), v.end(), [&dynamicVal](uint32_t& i){ i+=
            dynamicVal; });

    for(auto a : v)
    {
        std::cout << a << " ";
    }

    std::cout << "\n";
}
