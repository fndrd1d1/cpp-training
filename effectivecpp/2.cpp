#include <iostream>
#include <string>

using namespace std;

#define MACRORATIO 1.234 // avoid
/*
 * No symbol table entry
 * Multiple copies of the Macro if used at multiple places
 * No scope -> globally available
 */

const double RATIO = 1.234; // prefer
/*
 * Symbol available
 * Only one copy
 * could be put into a scope
 */

// Special Case 1: constant pointers
const char* const CNAME = "ratio";
// but prefer always a string
const string SNAME("ratio");

// Special Case 2: class specific constants
class Game {
private:
    static const int Num = 2;   // constant declaration
    /*
     * Only one copy for all Classes is created -> preferd
     * static const definition/declaration of built in types is allowed
     * if complex type -> define it in source file
     */
    int Scores[Num];            // use of constant
};

// Enum Hack
// If value of constant at compile time is needed
class Game2 {
private:
    enum { ASIZE = 2 }; // not possible to take an address from enum
    int a[ASIZE];
};

// Avoid function-like macros and replace by inline functions
template <typename T>
inline int maxi(const T& a, const T& b)
{
    return (a > b ? a : b);
}


/*
 * Simple constants prefer const objects or enums
 * Prefer inline functions to function macros
 * Use preprocessor for #include and #ifdef only
 */
int main()
{
    Game g;
    Game2 g2;

    //      avoid                   prefer
    cout << CNAME << " " <<         SNAME << "\n";
    cout << MACRORATIO << " " <<    RATIO << "\n";

    int a = 1;
    int b = 2;
    cout << maxi<int>(a,b) << "\n";
}
