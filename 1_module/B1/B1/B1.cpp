/*Найти лексикографически-минимальную строку, построенную по префикс-функции, в алфавите a-z*/

#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::string;
using std::set;
using std::vector;
using std::min;

//int recur_pi( const vector<int>& pi, const int x, int recur_depth )
//{
//	if (recur_depth <= 0) {
//		return pi[x - 1];
//	} else {
//		return recur_pi( pi, x, recur_depth - 1 );
//	}
//}

void recur_pi( set<char>& used_letters, const string& str, const vector<int>& pi, const int i )
{
	if (i < 0) return;
	used_letters.insert( str[i] );
	if (i > 0) {
		recur_pi( used_letters, str, pi, pi[i] );
	} 
	return;
}

string find_string( const vector<int>& pi )
{
	size_t n = pi.size();
	string str;
	str.resize( n );
	str[0] = 'a';
	for (size_t i = 1; i < n; i++) {
		if (pi[i] != 0) {
			str[i] = str[pi[i] - 1];
		} else {
			set<char> used_letters;

			for (int j = pi[i - 1]; j > 0; j = pi[j-1]) {
				used_letters.insert( str[j] );
			}
			
			for (char lett = 'b'; lett < 'z'; lett++) {
				if (!used_letters.count( lett )) {
					str[i] = lett;
					break;
				}
			}
		}
	}

	return str;
}

int main()
{
	int num = 0;
	vector<int> pi;
	while (cin >> num) {
		pi.push_back( num );
	}

	cout << find_string( pi );
	//system( "pause" );
	return 0;
}