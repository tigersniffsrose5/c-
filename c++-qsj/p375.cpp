#incude<bits/stdc++.h>

using namespace std;

void test()
{
	map<string, size_t> words_count;
	set<string> dir;
	string word;

	while ( cin >> word ) 
		++words_count[word];
	
	for ( const auto &a : words_count ) 
		cout << a.first << ' ' << a.second << endl;
	
	while ( cin >> word )
		if ( dir.find(word) == dir.end() )
			++words_count[word];
}

