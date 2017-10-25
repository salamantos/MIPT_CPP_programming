#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

#define alphabet_cardinality 150 // Мощность алфавита

vector<int> build_suffix_array( const string &s ) {
    size_t len = s.length();
    vector<size_t> counter( alphabet_cardinality ); // Для стабильной сортировки подсчетом
    vector<int> perm( len ); // Массив перестановок в отсортированном виде
    vector<int> classes( len ); // Массив классов эквивалентности равных символов

    // База индукции - нулевая итерация алгоритма
    // Считаем количество одинаковых символов
    for (int i = 0; i < len; ++i) {
        ++counter[s[i]];
    }
    // Считаем границы классов эквивалентности одинаковых символов
    for (int i = 1; i < alphabet_cardinality; ++i) {
        counter[i] += counter[i - 1];
    }
    // В соответствии с классами заполняем массив
    for (int i = 0; i < len; ++i) {
        perm[--counter[s[i]]] = i;
    }
    classes[perm[0]] = 0;
    int count_classes = 1;
    for (int i = 1; i < len; ++i) {
        if (s[perm[i]] != s[perm[i - 1]]) ++count_classes;
        classes[perm[i]] = count_classes - 1;
    }

    // Переход - от (k-1)й итерации к (k)й
    vector<int> perm_new( len ); // Массив перестановок в отсортированном виде
    vector<int> classes_new( len ); // Массив классов эквивалентности равных символов
    for (int h = 0; (1 << h) < len; ++h) {
        for (int i = 0; i < len; ++i) {
            perm_new[i] = perm[i] - (1 << h);
            if (perm_new[i] < 0) perm_new[i] += len;
        }
        vector<size_t> counter( count_classes );
        for (int i = 0; i < len; ++i)
            ++counter[classes[perm_new[i]]];
        for (int i = 1; i < count_classes; ++i)
            counter[i] += counter[i - 1];
        for (int i = len - 1; i >= 0; --i)
            perm[--counter[classes[perm_new[i]]]] = perm_new[i];
        classes_new[perm[0]] = 0;
        count_classes = 1;
        for (int i = 1; i < len; ++i) {
            int mid1 = (perm[i] + (1 << h)) % len, mid2 = (perm[i - 1] + (1 << h)) % len;
            if (classes[perm[i]] != classes[perm[i - 1]] || classes[mid1] != classes[mid2])
                ++count_classes;
            classes_new[perm[i]] = count_classes - 1;
        }
        perm_new = perm;
        classes = classes_new;
    }

    return perm;
}

vector<int> the_algorithm_of_Kasai_Arimura_Arikawa_Lee_Park( const vector<int> &suffix_array, const string &s ) {
    size_t len = s.length();
    vector<int> lcp( len );
    vector<int> inverted_lcp( len );
    for (int i = 0; i < len; ++i) {
        inverted_lcp[suffix_array[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < len; ++i) {
        if (k > 0) --k;
        if (inverted_lcp[i] == len - 1) {
            lcp[len - 1] = -1;
            k = 0;
        } else {
            int j = suffix_array[inverted_lcp[i] + 1];
            while (i + k < len and j + k < len and s[i + k] == s[j + k]) ++k;
            lcp[inverted_lcp[i]] = k;
        }
    }
    return lcp;
}

int main() {
    string s;
    cin >> s;
    s += '#';

    vector<int> suffix_array = build_suffix_array( s );

    vector<int> lcp = the_algorithm_of_Kasai_Arimura_Arikawa_Lee_Park( suffix_array, s );

    size_t len = s.length() - 1;
    int sum = 0;
    for (size_t i = 0; i <= len; ++i) {
        sum += (len - suffix_array[i]);
    }
    for (size_t i = 0; i < len; ++i) {
        sum -= (lcp[i]);
    }
    cout<<sum;

    return 0;
}