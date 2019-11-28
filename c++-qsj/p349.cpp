#include <bits/stdc++.h>

using namespace std;

vector<string> words = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};


void biggies( vector<string> &words, vector<string>::size_type sz )
{
    elimDups(words);
    stable_sort(words.begin(), words.end(), [](const string &a, const string &b) 
                { return a.size() < b.size();});
    auto wc = find_if(words.begin(), words.end(), [sz](const string &a)i
                      { return a.size() >= sz; });
    auto count = words.end() - wc;
    cout << count << endl;
    for_each(wc, words.end(), [](const string &s) {cout << s << " ";});
    cout << endl;
}
void elimDups( vector<string> &words ) 
{
    sort(words.begin(), word.end());
    auto end_unique = unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}

bool isShorter( const string &s1, const string &s2 )
{
    return s1.size() < s2.size();
}

int main()
{
    elimDups(word);  //按字典序排序，并消除重复元素
    stable_sort(word.begin(), word.end(), isShorter); //按长度排序，长度相同的按字典序排序
    for ( const auto &s : word ) //范围for循环
        cout << s << " ";    //打印元素
    
    cout << endl;

    return 0;
}

