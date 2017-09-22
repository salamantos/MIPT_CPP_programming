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

vector<int> Z_to_prefix( const vector<int>& z )
{
	size_t z_len = z.size();
	vector<int> p( z_len, 0 );
	for (int i = 1; i <= z_len - 1; i++) {
		for (int j = z[i] - 1; j >= 0; j--) {
			if (p[i + j] > 0) {
				break;
			} else {
				p[i + j] = j + 1;
			}
		}
	}
	return p;
}

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
	for (size_t i = 0; i < n; i++) {
		if (pi[i] != 0) {
			str[i] = str[pi[i] - 1];
		} else {
			if (i == 0) {
				str[0] = 'a';
				continue;
			}
			set<char> used_letters;

			for (int j = pi[i - 1]; j > 0; j = pi[j - 1]) {
				used_letters.insert( str[j] );
			}
			used_letters.insert( str[0] );

			for (char lett = 'a'; lett < 'z'; lett++) {
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
	vector<int> z;
	while (cin >> num) {
		z.push_back( num );
	}

	cout << find_string( Z_to_prefix( z ) );
	//system( "pause" );
	return 0;
}
