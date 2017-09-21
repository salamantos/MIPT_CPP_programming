/*Найдите все вхождения шаблона в строку. Длина шаблона – p, длина строки ­– n. Время O(n + p), доп. память – O(p).
-> Вариант 1. С помощью префикс-функции;
   Вариант 2. С помощью z-функции.
Формат входного файла
Шаблон, символ перевода строки, строка.
Формат выходного файла
Позиции вхождения шаблона в строке.
Время: 100мс, память 3Mb.*/

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::string;
using std::vector;

vector<int> find_prefix_func( string& str )
{
	size_t len = str.length();
	vector<int> prefix_func( len );
	for (size_t i = 1; i < len; i++) {
		size_t j = prefix_func[i - 1];
		while (j > 0 && str[i] != str[j]) {
			j = prefix_func[j - 1];
		}
		if (str[i] == str[j]) ++j;
		prefix_func[i] = j;
	}

	return prefix_func;
}

int main()
{
	string pattern;
	string str;
	cin >> pattern >> str;
	size_t p = pattern.length();
	size_t s = str.length();
	vector<int> prefix_func = find_prefix_func( str );
	str = pattern + '#' + str;
	for (size_t i = 0; i < p + s + 1; i++) {
		if (prefix_func[i] == p) {
			cout << i - 2 * p << '\n';
		}
	}

	return 0;
}