#pragma once

#include<iostream>
#include<cstring>

using namespace std;

class my_string {
    
    friend ostream& operator<< (ostream &os, const my_string& str);
    friend istream& operator>> (istream &is, const my_string& str);

public:
    
    size_t len;

    my_string();
    my_string(const char *str);  
    my_string(const my_string& str);
    my_string(size_t n, char s);
    my_string(const my_string& str, size_t pos);
    ~my_string();

    char& operator[] (size_t i);
    my_string& operator= (const my_string& str);
    my_string& operator= (const char *str);    
    my_string operator+ (const my_string& str);
    my_string operator+ (const char *str);
    my_string& operator+= (const my_string& str);
    my_string& operator+= (const char *str);

    bool operator> (const my_string& str);
    bool operator> (const char *str);
    bool operator< (const my_string& str);
    bool operator< (const char *str);
    bool operator!= (const my_string& str);
    bool operator!= (const char *str);
    bool operator== (const my_string& str);
    bool operator== (const char *str);

    bool empty();
    size_t size();
    my_string& erase(size_t pos, size_t Len);

private:

    char *data;

public:

    class iterator {

    public:

        iterator()
        {
            it = new my_string();
            i = 0;
        }

        iterator(const my_string* str, size_t i)
        {
           it = new my_string(*str);
           it->len = str->len;
           this->i = i;
        }

        ~iterator()
        {
            if ( it ) {
                delete it;
                it = nullptr;
                i = 0;
            }
        }
        
        iterator& operator= (const iterator p)
        {
            if ( p.it == nullptr ) {
                this->it = nullptr;
                i = 0;
            }

            else {
                this->i = p.i;
                this->it = new my_string(*(p.it));
            }
            
            return *this;
        }

        char& operator* ()
        {
            return this->it->data[i];
        }   

        bool operator== (const iterator its)
        {
            if( its.i == this->i && its.it == this->it ) 
                return true ;

            else 
                return false ;
        }
        
        bool operator!= (const iterator its)
        {
            return this->i == its.i ? false : true;
        }

        void operator++ ()
        {
            ++this->i;
        }

        void operator++(int l)
        {
            l = 1;
            this->i += l ;
        }

    private:

        my_string *it;
        size_t i;

    };

public:

    iterator begin() 
    {
        size_t i = 0;
        iterator its = iterator(this, i);

        return its;
    }

    iterator end()
    {
        size_t l = strlen(this->data);

        return  iterator(this, l);
    }


};

my_string::my_string()
{
    this->data = nullptr;
    this->len = 0;
}

my_string::my_string(const char *str)
{
    if ( str == nullptr ) {
        this->data = nullptr;
        this->len = 0;
    }

    else {
        this->data = new char[strlen(str)+1];
        strcpy(this->data, str);
        this->len = strlen(str);
    }
}

my_string::my_string(const my_string& str)
{
    if ( str.data == nullptr ) {
        this->data = nullptr;
        this->len = 0;
    }

    else{
        this->data = new char[strlen(str.data)+1];
        strcpy(this->data, str.data);
        this->len = str.len;
    }
}

my_string::my_string(size_t n, char s)
{
    this->data = new char[n+1];

    for ( size_t i = 0; i < n; ++i ) 
        this->data[i] = s;

    this->len = n;
}

my_string::my_string(const my_string& str, size_t pos)
{
    if ( pos > str.len ) {
        cout << "subscript out of range" << endl;
        exit(0);
    }

    else {
        this->data = new char[str.len-pos+1];
        strncpy(this->data, str.data+pos, str.len-pos);
    }
}

my_string::~my_string()
{
    if ( this->data ) {
        delete[] this->data;
        this->data = nullptr;
        this->len = 0;
    }
}

ostream& operator<< (ostream& os, const my_string& str)
{
    os << str.data;
    return os;
}

istream& operator>> (istream& is, const my_string& str)
{
    is >> str.data;
    return is;
}

char& my_string::operator[](size_t i) 
{
    if ( i > len ) {
        cout << "subscript out of range" << endl;
        exit(0);
    }

    else 
        return data[i];
}

my_string& my_string::operator= (const my_string& str)
{
    if ( this != &str ) {
        
        delete[] this->data;
        this->data = nullptr;
        this->len = 0;

        if ( str.data == nullptr ) { 
            this->data = nullptr;
            this->len = 0;
        }
    
        else {
            this->data = new char[strlen(str.data)+1];
            strcpy(this->data, str.data);
            this->len = str.len;
        }
    }
    
    return *this;
}

my_string& my_string::operator= (const char *str)
{

    delete[] this->data;
    this->data = nullptr;
    this->len = 0;

    if ( str == nullptr ) {
        this->data = nullptr;
        this->len = 0;
    }

    else {
        this->data = new char[strlen(str)+1];
        strcpy(this->data, str);
        this->len = strlen(str);
    }

    return *this;
}

my_string my_string::operator+ (const my_string& str)
{
    my_string newstr;
    
    if ( str.data == nullptr )
        return *this;
    
    else {
        newstr.data = new char[strlen(str.data)+strlen(this->data)+1];
        strcpy(newstr.data, this->data);
        strcat(newstr.data, str.data);
        newstr.len = strlen(newstr.data);
    }

    return newstr;
}

my_string my_string::operator+ (const char *str)
{
    my_string newstr;

    if ( str == nullptr )
        return *this;

    else {
        newstr.data = new char[strlen(str)+strlen(this->data)+1];
        strcpy(newstr.data, this->data);
        strcat(newstr.data, str);
        newstr.len = strlen(newstr.data);
    }

    return newstr;
}

my_string& my_string::operator+= (const my_string& str)
{
    if ( str.data == nullptr )
        return *this;

    else {
        char *s = new char[strlen(str.data)+strlen(this->data)+1];
        strcpy(s, this->data);
        strcat(s, str.data);
        
        delete[] this->data;
        this->data = new char[strlen(s)+1];

        strcpy(this->data, s);
        delete[] s;
        
        this->len = strlen(this->data);

        return *this;
    }
}

my_string& my_string::operator+= (const char *str)
{
    if ( str == nullptr )
        return *this;

    else {
        char *s = new char[strlen(str)+strlen(this->data)+1];
        strcpy(s, this->data);
        strcat(s, str);
        
        delete[] this->data;
        this->data = new char[strlen(s)+1];

        strcpy(this->data, s);
        delete[] s;

        this->len = strlen(this->data);

        return *this;
    }
}

bool my_string::operator> (const my_string& str)
{
    if ( strcmp(this->data, str.data) > 0 )
        return true;
    
    else
        return false;
}

bool my_string::operator> (const char *str)
{
    if ( strcmp(this->data, str) > 0 )
        return true;
    
    else
        return false;
}

bool my_string::operator< (const my_string& str)
{
    if ( strcmp(this->data, str.data) < 0 )
        return true;
    
    else
        return false;
}

bool my_string::operator< (const char *str)
{
    if ( strcmp(this->data, str) < 0 )
        return true;
    
    else
        return false;
}

bool my_string::operator!= (const my_string& str)
{
    if ( strlen(this->data) == strlen(str.data) )
        return false;

    else 
        return strcmp(this->data, str.data) ? true : false;
}

bool my_string::operator!= (const char *str)
{
    if ( strlen(this->data) == strlen(str) )
        return false;

    else 
        return strcmp(this->data, str) ? true : false;
}

bool my_string::operator== (const my_string& str)
{
    if ( strlen(this->data) != strlen(str.data) )
        return false;

    else 
        return strcmp(this->data, str.data) ? false : true;
}

bool my_string::operator== (const char *str)
{
    if ( strlen(this->data) != strlen(str) )
        return false;

    else 
        return strcmp(this->data, str) ? false : true;
}

bool my_string::empty()
{
    if ( len == 0 )
        return true;

    else 
        return false;
}

size_t my_string::size()
{
    return len;
}

my_string& my_string::erase(size_t pos, size_t Len)
{
    size_t l = len-Len;

    char *ptr = new char[l];
    strncpy(ptr, data, pos);
    strcpy(ptr+pos, data+pos+Len);

    delete[] data;
    data = ptr;
    len = l;

    return *this;
}
