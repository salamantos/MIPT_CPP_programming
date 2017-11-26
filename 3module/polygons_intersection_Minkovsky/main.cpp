#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define _USE_MATH_DEFINES // for pi constant
using std::vector;
using std::cin;
using std::cout;
using std::atan2;
using std::reverse;
#define pi M_PI

struct Point {
    double _x = 0, _y = 0;

    Point( double x, double y ) : _x( x ), _y( y ) {}

    Point() = default;

    bool operator<( const Point& other ) const {
        // Самая нижняя самая левая
        if (this->_y < other._y) {
            return true;
        } else if (this->_y == other._y and this->_x < other._x) {
            return true;
        } else {
            return false;
        }
    }

    Point operator+( const Point& other ) const {
        return Point( this->_x + other._x, this->_y + other._y );
    }
};

void read_polygon( vector<Point>& Pol, size_t len, int koef ) {
    for (int i = 0; i < len; ++i) {
        double x = 0, y = 0;
        cin >> x >> y;
        Pol.emplace_back( Point( x * koef, y * koef ));
    }
    reverse( Pol.begin(), Pol.end());
}

// Считает полярный угол
double angle( const Point& a, const Point& b ) {
    double temp = atan2((b._y - a._y), (b._x - a._x));
    return temp >= 0 ? temp : temp + 2 * pi;
}

vector<Point>
find_Minkowski_addition( const vector<Point>& V, const vector<Point>& W, const size_t n, const size_t m ) {
    // Находим самую левую самую правую точку в каждом многоугольнике
    Point V_min = V[0];
    size_t V_min_index = 0;
    for (size_t k = 1; k < n; ++k) {
        if (V[k] < V_min) {
            V_min = V[k];
            V_min_index = k;
        }
    }
    Point W_min = W[0];
    size_t W_min_index = 0;
    for (size_t k = 1; k < m; ++k) {
        if (W[k] < W_min) {
            W_min = W[k];
            W_min_index = k;
        }
    }

    auto i = static_cast<int>(V_min_index), j = static_cast<int>(W_min_index);
    int V_is_traversed = 0, W_is_traversed = 0;
    vector<Point> res;
    while ((V_is_traversed != 2) and (W_is_traversed != 2)) {
        Point temp_point = V[i % n] + W[j % m];
        res.push_back( temp_point );
        if (angle( V[i % n], V[(i + 1) % n] ) < angle( W[j % m], W[(j + 1) % m] )) {
            ++i;
            if (i % n == (V_min_index + 1) % n) {
                V_is_traversed += 1;
            }
        } else if (angle( V[i % n], V[(i + 1) % n] ) > angle( W[j % m], W[(j + 1) % m] )) {
            ++j;
            if (j % m == (W_min_index + 1) % m) {
                W_is_traversed += 1;
            }
        } else {
            ++i;
            if (i % n == (V_min_index + 1) % n) {
                V_is_traversed += 1;
            }
            ++j;
            if (j % m == (W_min_index + 1) % m) {
                W_is_traversed += 1;
            }
        }
    }
    return res;
}

int sign( double val ) {
    return (val > 0 ? 1 : (val < 0 ? -1 : 0));
}

bool check_0_0( const vector<Point>& Minkowski_add ) {
    for (int i = 0; i < Minkowski_add.size(); ++i) {
        auto Pi = Minkowski_add[i];
        auto Pi1 = Minkowski_add[i + 1];
        if (Pi._x * Pi1._y - Pi._y * Pi1._x < 0) {
            return false;
        }
        if (Pi._x * Pi1._y - Pi._y * Pi1._x == 0) {
            if (Pi._x != Pi1._x or Pi._y != Pi1._y) {
                if (sign( Pi._x ) == sign( Pi1._x ) == 0) {
                    if (sign( Pi._y ) == 0 or sign( Pi1._y ) == 0) {
                        return true;
                    } else if (sign( Pi._y ) != sign( Pi1._y )) {
                        return true;
                    } else if (sign( Pi._y ) == sign( Pi1._y )) {
                        return false;
                    }
                } else {
                    if (sign( Pi._x ) == 0) {
                        if (sign( Pi._y ) == 0) {
                            return true;
                        }
                        return false;
                    }
                    if (sign( Pi1._x ) == 0) {
                        if (sign( Pi1._y ) == 0) {
                            return true;
                        }
                        return false;
                    }
                    if (sign( Pi._x ) != sign( Pi1._x )){
                        if (sign( Pi._y ) != sign( Pi1._y )) {
                            return true;
                        }
                        if (sign( Pi._y ) == sign( Pi1._y )) {
                            return false;
                        }
                    }

                }
            }
        }
    }
    return true;
}

int main() {
    size_t n = 0;
    cin >> n;
    vector<Point> V;
    read_polygon( V, n, -1 ); // Отражаем многоугольник относительно y=-x

    size_t m = 0;
    cin >> m;
    vector<Point> W;
    read_polygon( W, m, 1 );

    vector<Point> Minkowski_add = find_Minkowski_addition( V, W, n, m );

    cout << (check_0_0( Minkowski_add ) ? "YES" : "NO");

    return 0;
}