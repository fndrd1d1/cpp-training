#include <iostream>

using namespace std;

class Integer
{
public:
    Integer(int n)
    : num(n)
    {}

    int num;
};

const Integer operator*(const Integer& lhs, const Integer& rhs)
{
    return Integer(lhs.num * rhs.num);
}


int main()
{
    Integer i(4);
    Integer j(5);
    Integer ij = i * j;

    cout << i.num << " * " << j.num << " = " << ij.num << "\n";
}