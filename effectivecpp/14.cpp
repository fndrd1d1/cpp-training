#include <iostream>

using namespace std;

namespace m
{
class Mutex
{
  public:
    Mutex()
        : id(i)
    {
        i++;
    }

    int id;

  private:
    static int i;
};

int Mutex::i = 0;

void lock(Mutex *m)
{
    cout << "lock " << m->id << "\n";
}

void unlock(Mutex *m)
{
    cout << "unlock " << m->id << "\n";
}

// solution
class Lock
{
  public:
    explicit Lock(Mutex *pm)
        : m(pm, unlock)
    {
        lock(m.get());
    }
  private:
    shared_ptr<Mutex> m;
};
} // namespace m

int main()
{
    ::m::Mutex m1;
    ::m::Mutex m2;
    ::m::Lock l(&m1);
    ::m::Lock l2(&m2);

    // Problem:
    // What should happen with when an RAII object is copied?
    ::m::Lock l3(l);

    // Solution 1:
    // Make it uncopyable

    // Solution 2:
    // Use reference counting for the underlying resource
}