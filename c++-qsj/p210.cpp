//如果我们在内层作用域中声明名字，它将隐藏外层作用域中声明的同名实体.在不同作用域中无法重载函数名. 
string read();
void print(const string &);
void print(double);
void foBar(int ival);
{
    bool read = false;  //隐藏外层的read
    string s = read();  //read不是函数，而是一个bool值
    //局部变量中声明函数是一个不好的习惯
    void print(int);   //隐藏了之前的print
    print("Value: ");  //print（const string &）被隐藏了
    print(ival);      //当前的print（int）可见
    print(3.14);      //调用print（int），print（double）被隐藏了
}

