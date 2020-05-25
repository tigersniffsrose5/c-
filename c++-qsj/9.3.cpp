//qsj
#include <bits/stdc++.h>

using namespace std;

bool find(vector<int>::iterator begin, vector<int>::iterator end, int value)
{
    for ( auto iter = begin; iter != end; ++iter )
        if ( *iter == value )
            return true;
    return false;
}

vector<int>::iterator Find(vector<int>::iterator begin, vector<int>::iterator end, int value)
{
    for ( auto iter = begin; iter != end; ++iter )
        if ( *iter == value )
            return iter;
    return end;
}


