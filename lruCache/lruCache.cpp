#include <list>
#include <unordered_map>
#include <cstdint>
#include <iostream>
#include <string>

template<typename T>
class LruCache {
public:
    using const_iterator = typename std::list<T>::const_iterator;
    using iterator = typename std::list<T>::iterator;

    explicit LruCache(uint32_t s)
    : m(s)
    , maxSize(s)
    {
    }

    void insert(T key)
    {
        // already in cache
        if (m.find(key) != m.end())
        {
            dq.erase(m[key]);
            dq.push_front(key);
            m[key] = dq.begin();
        }
        else // not in cache
        {
            // cache not full
            if (m.size() < maxSize)
            {
                dq.push_front(key);
                m[key] = dq.begin();
            }
            else // cache full
            {
                m.erase(dq.back());
                dq.pop_back();
                dq.push_front(key);
                m[key] = dq.begin();
            }
        }
    }

    bool find(T key)
    {
        if(m.find(key) != m.end())
        {
            insert(key);
            return true;
        }
        else
        {
            return false;
        }
    }

    const_iterator cbegin() const
    {
        return dq.cbegin();
    }

    const_iterator cend() const
    {
        return dq.cend();
    }

    iterator begin()
    {
        return dq.begin();
    }

    iterator end()
    {
        return dq.end();
    }

private:
    std::list<T> dq;
    std::unordered_map<T, typename std::list<T>::iterator> m;
    uint32_t maxSize;
};

template<typename T>
void print(LruCache<T> &lru)
{
    for (const auto &it : lru)
    {
        std::cout << it << " ";
    }
    std::cout << "\n";
}

int main()
{
    LruCache<uint32_t> lru(3);
    lru.insert(1);
    print(lru);

    lru.insert(2);
    print(lru);

    lru.insert(1);
    print(lru);

    lru.insert(3);
    print(lru);

    std::cout << lru.find(1) << "\n";
    print(lru);

    lru.insert(4);
    print(lru);

    lru.insert(1);
    print(lru);

    LruCache<std::string> lru2(3);
    lru2.insert("hi");
    lru2.insert("he");
    lru2.insert("ho");

    print(lru2);
}
