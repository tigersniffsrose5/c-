#include <bits/stdc++.h>

using namespace std;

int main()
{
    auto pointer = std::make_shared<string>(10, 'a');
    shared_ptr<string> pointer2(pointer); // 引用计数+1
    shared_ptr<string> pointer3(pointer); // 引用计数+1

    cout << *pointer << endl;
    cout << *pointer2 << endl;
    cout << *pointer3 << endl;
    cout << pointer.use_count() << endl;
    cout << pointer2.use_count() << endl;
    cout << pointer3.use_count() << endl;
 
    if ( !pointer.unique() ) 
        pointer.reset(new string(*pointer));

    cout << *pointer << endl;
    cout << *pointer2 << endl;
    cout << *pointer3 << endl;
    cout << pointer.use_count() << endl;
    cout << pointer2.use_count() << endl;
    cout << pointer3.use_count() << endl;
    
    *pointer += "bbb";

    cout << *pointer << endl;
    cout << *pointer2 << endl;
    cout << *pointer3 << endl;
    cout << pointer.use_count() << endl;
    cout << pointer2.use_count() << endl;
    cout << pointer3.use_count() << endl;

    return 0;

}
