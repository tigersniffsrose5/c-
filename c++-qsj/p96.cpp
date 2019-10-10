#include <iostream>

using namespace std;

int main()
{
    string s = "some string";
    for ( auto it = s.begin(); it != s.end() && !isspace(*it); ++it )   //isspace()若字符为空格则为真
        *it = toupper(*it); 
    cout << s << endl;
    return 0;
}

