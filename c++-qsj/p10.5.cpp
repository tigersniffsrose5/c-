#include <algorithm>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main()
{
    char c1[10] = "eipi10";
    char c2[10] = "eipi10";
    vector<char*> roster1{c1};
    list<char*> roster2{c2};
    cout << equal(roster1.cbegin(), roster1.cend(), roster2.cbegin()) << endl;;
    return 0;
}

