#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<int> v1;
    vector<string> text;
    string word;
    
    for ( int i = 0; i != 100; i++ )
        v1.push_back(i);
    
    while (cin >> word) {
        text.push_back(word);
    }

    return 0;
}

