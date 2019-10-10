#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    string s("Hello World!!!");
    for (auto &c : s)
        c = toupper(c);   //c是一个引用,因此赋值语句将改变s中字符的值
    cout << s << endl;
    return 0;
}

