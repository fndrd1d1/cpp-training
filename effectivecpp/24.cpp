#include <iostream>

class Integer
{
public:
    Integer(int num)
    : n(num)
    {}

    int n;
};

// make it a non-member non-friend function if implict conversion should
// be allowed for all parameters

// from left to right
// 1. const: avoids 3=2+1 problem. Used = instead ==
// 2. return by value: return type runs out of scope, what should it reference?
// 3. const T&: efficient (no ctor, dtor) and avoids slicing problem
const Integer operator*(const Integer& lhs, const Integer& rhs)
{
    return Integer(lhs.n * rhs.n);
}


int main()
{
    Integer i(2);
    Integer g = 2 * i;
    Integer l = i * 2;
}