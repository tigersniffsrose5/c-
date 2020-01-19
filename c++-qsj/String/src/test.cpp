#include<my_string.hpp>

int main()
{
    my_string s1 = "qsj";
    my_string s2 = "world";

    my_string s3 = s1;
    s3 += s2;

    cout << s3 << endl;
    cout << s3.size() << endl;

    for ( my_string::iterator it = s3.begin(); it != s3.end(); ++it ) 
        cout << *it << endl;

    s3.erase(0, 3);

    cout << s3 << endl;

    return 0;
}

