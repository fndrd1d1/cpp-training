#include <iostream>
#include <vector>

using namespace std;

class Widget {

public:

    Widget()
    : v(new vector<int>())
    {
    }



    ~Widget()
    {
        delete v;
    }

    // bad copy assignment
    // copy to self let's a pointer dangle
    /*
    Widget& operator=(const Widget& rhs)
    {
        delete v;
        v = new vector<int>(*rhs.v);
        return *this; // allow chaining of assignments
    }
    */

    // better copy assignment
    // copy to self is avoided
    // not exception safe
    /*
    Widget& operator=(const Widget& rhs)
    {
        if(this == &rhs) return *this;

        delete v;
        v = new vector<int>(*rhs.v);
        return *this; // allow chaining of assignments
    }
    */

    // even better copy assignment
    // copy to self is avoided
    // exception safe by reordering
    /*
    Widget& operator=(const Widget& rhs)
    {
        vector<int> *org = v;
        v = new vector<int>(*rhs.v);
        delete org;
        return *this; // allow chaining of assignments
    }
    */

    // copy and swap idiom to the rescue
    // needs a valid copy constructor
    Widget(const Widget& rhs)
    : v(new vector<int>(*rhs.v))
    {
    }

    // copy to self is avoided
    // excpetion safe
    Widget& operator=(Widget rhs) // copy in parameter -> allows compiler optimization
    {
        swap(*this, rhs);

        return *this; // allow chaining of assignments
    }

    friend void swap(Widget& first, Widget& second)
    {
        using std::swap;
        swap(first.v, second.v);
    }
private:


    vector<int> *v;
};

int main()
{
    Widget w;
    Widget w2;

    w = w;
}
