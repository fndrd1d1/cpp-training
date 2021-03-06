#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

/*
    Examples for non-modifying algorithms in the STL.


*/

template <typename T>
void forEachPrint(const std::vector<T> &vec)
{
    auto print = [](const uint32_t &i) {
        std::cout << i << " ";
    };
    std::for_each(begin(vec), end(vec), print);
    std::cout << "\n";
}

template <typename T>
void anyOfBigger5(const std::vector<T> &vec)
{
    auto isBiggerThan5 = [](T i) {
        return i > 5;
    };

    if (std::any_of(begin(vec), end(vec), isBiggerThan5))
    {
        std::cout << "One element bigger than 5\n";
    }
}

template <typename T>
void noneOfIs9(const std::vector<T> &vec)
{
    auto noneOfIs9 = [](T i) {
        return i == 9;
    };

    if (std::none_of(begin(vec), end(vec), noneOfIs9))
    {
        std::cout << "No element is equal to 9\n";
    }
}

template <typename T>
void count1s(const std::vector<T> &vec)
{
    const T count1s = std::count(begin(vec), end(vec), 1);
    std::cout << "Count 1s = " << count1s << "\n";
}

template <typename T>
void countOdd(const std::vector<T> &vec)
{
    auto isOdd = [](T i) {
        return ((i & 1) == 1);
    };

    const T countOdds = std::count_if(begin(vec), end(vec), isOdd);
    std::cout << "Count odd = " << countOdds << "\n";
}

template <typename T>
void findConsecutiveElements(const std::vector<T> &vec)
{
    auto it = std::adjacent_find(begin(vec), end(vec));

    if (it != vec.end())
    {
        std::cout << "First consecutive element = " << *it << " at position = " << std::distance(begin(vec), it) << "\n";
    }
}

template <typename T>
void haveSameElements(const std::vector<T> &vec1, const std::vector<T> &vec2)
{
    if (std::is_permutation(begin(vec1), end(vec1), begin(vec2)))
    {
        std::cout << "Both vectors contain the same elements\n";
    }
}

template <typename T>
void searchForMultipleConsecutiveElements(const std::vector<T> &vec, const std::vector<T> &elements)
{
    // returns the iterator pointing to the first element in vec
    auto it = std::search(begin(vec), end(vec), begin(elements), end(elements));

    if (it != vec.end())
    {
        std::cout << "First consecutive element (" << *it << ") found at position " << it - vec.begin() << "\n";
    }
    else
    {
        std::cout << "No element found\n" ;
    }

}

template <typename T>
void searchForSameConsecutiveElement(const std::vector<T> &vec, T value, size_t count)
{
    auto it = std::search_n(begin(vec), end(vec), value, count);

    if (it != vec.end())
    {
        std::cout << "First consecutive element (" << *it << ") found at position " << it - vec.begin() << "\n";
    }
    else
    {
        std::cout << "No element found\n";
    }
}

static const uint32_t FROM = 1;
static const uint32_t TO = 9;
static const size_t COUNT = 10;

int main(int argc, char *argv[])
{
    const auto seed = ::std::chrono::system_clock::now().time_since_epoch().count();

    std::default_random_engine gen(seed);
    std::uniform_int_distribution<uint32_t> dist(FROM, TO);

    auto genRandom = [&dist, &gen]() {
        return dist(gen);
    };

    std::vector<uint32_t> vec(COUNT);

    // modifying algorithm to fill the vector
    std::generate(begin(vec), end(vec), genRandom);

    // for_each
    forEachPrint(vec);

    // any_of
    anyOfBigger5(vec);

    // none_of
    noneOfIs9(vec);

    // count
    count1s(vec);

    // count_if
    countOdd(vec);

    // adjacent_find
    findConsecutiveElements(vec);

    // is_permutation
    {
        gen.seed(::std::chrono::system_clock::now().time_since_epoch().count());
        std::vector<uint32_t> vec2(COUNT);
        std::generate(begin(vec2), end(vec2), genRandom);

        haveSameElements(vec, vec2);
    }

    // search
    {
        std::vector<uint32_t> elements(COUNT/2);
        std::copy_n(begin(vec), elements.size(), begin(elements));

        searchForMultipleConsecutiveElements(vec, elements);
    }

    // search_n
    {
        uint32_t value = 5;
        searchForSameConsecutiveElement(vec, value, 2);
    }
}