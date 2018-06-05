/*Найти лексикографически-минимальную строку, построенную по префикс-функции, в алфавите a-z*/

#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::string;
using std::unordered_set;
using std::vector;
using std::min;

string find_string( const vector<int>& pi )
{
	const size_t n = pi.size();
	string str;
	str.resize( n );
	str[0] = 'a';
	for (size_t i = 1; i < n; i++) {
		if (pi[i] != 0) {
			str[i] = str[pi[i] - 1];
		} else {
			unordered_set<char> used_letters;

			for (int j = pi[i - 1]; j > 0; j = pi[j-1]) {
				used_letters.insert( str[j] );
			}
			
			for (char lett = 'b'; lett < 'z'; lett++) {
				if (used_letters.count( lett ) == 0) {
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
