#include <iostream>
#include <vector>

using namespace std;

class Rational {
public:
    Rational(int value) : r(value) {}

    int getValue() const
    {
        return r;
    }

private:
    int r;
};

// should return CONST otherwise it's possible to call assign operator on return value
const Rational operator*(const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs.getValue()*rhs.getValue());
}

int main()
{
    vector<int> v(3);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;

    const vector<int>::iterator it = v.begin(); // like T* const
    *it = 10;
    // it++; // not possible
    //

    vector<int>::const_iterator cit = v.begin();
    cit++;
    // *cit = 20; // not possible

    for (vector<int>::const_iterator i = v.begin() ; i < v.end(); ++i)
    {
        cout << *i << " ";
    }

    cout << ".. \n";
    Rational a(1);
    Rational b(2);

    Rational c(2);

    Rational result = a*b;
    cout << result.getValue();

    // not possible with const operator*
    /*
    if(a*b=c)
    {
        cout << "wtf\n";
    }
    */
}
