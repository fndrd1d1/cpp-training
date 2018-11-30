#include <iostream>
#include <string.h>
#include <algorithm>


// Task
// provide non throwing swap
// for following PImpl Idiom example

// normal std::swap is not efficient in this case
// a swap of the pointers is way more efficient

class WorkerImpl
{
public:
    WorkerImpl(int p, std::string n)
    : prio(p)
    , name(n)
    {}

    int getPrio()
    {
        return prio;
    }

    void work()
    {
        std::cout << name << " is working\n";
    }

private:
    int prio;
    std::string name;

};

class Worker
{
public:
    Worker(int prio, std::string name)
    : wImpl(std::make_shared<WorkerImpl>(prio, name))
    {}

    int getPrio() const { return wImpl->getPrio(); }
    void work() { wImpl->work(); }

    // 1. provide public member function
    // never throws an exception
    // operation on built in types (=pointers)
    // never throws
    void swap(Worker& other)
    {
        using std::swap;

        swap(wImpl, other.wImpl);
    }

private:
    std::shared_ptr<WorkerImpl> wImpl;
};

// 2. provide non-member swap in same namespace as class
void swap(Worker& a, Worker& b)
{
    a.swap(b);
}

// 3. in case of non class template
// provide specialization of std::swap for your class
namespace std {
    template<>
    void swap<Worker>(Worker& a, Worker& b)
    {
        a.swap(b);
    }
}

// Problem

int main()
{
    Worker w(10, "Henriette");
    w.work();
}