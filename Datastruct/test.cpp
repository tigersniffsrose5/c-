#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct great {
    bool operator() ( const T &left, const T &right ) {
        return left > right;
    }
};

int main ()
{
    priority_queue<int, vector<int>, great<int>> a;
    priority_queue<int> c;

    for ( int i = 0; i < 5; ++i ) {
        a.push(i);
        c.push(i);
    }

    cout << "a:" << endl;
    while ( !a.empty() ) {
        cout << a.top() << endl;
        a.pop();    
    }

    cout << "c:" << endl;
    while ( !c.empty() ) {
        cout << c.top() << endl;
        c.pop();
    }

    return 0;
}
