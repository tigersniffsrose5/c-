#include <bits/stdc++.h>

using namespace std;

int main()
{
    forward_list<int> flst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto prve = flst.before_begin();
    auto curr = flst.begin();

    while ( curr != flst.end() ) {
        if ( *curr % 2 )
            curr = flst.erase_after(prve);
        else {
            prve = curr;
            ++curr;
        }
    }
    
    return 0;
}

