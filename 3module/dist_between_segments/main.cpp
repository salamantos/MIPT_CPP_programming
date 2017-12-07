/*
 * Даны два отрезка в пространстве (x1, y1, z1) - (x2, y2, z2) и (x3, y3, z3) - (x4, y4, z4).
 * Найдите расстояние между отрезками.
*/

#include <cmath>
#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::setprecision;

#define eps 1e-9

struct Point {
    double _x = 0, _y = 0, _z = 0;

    Point( double x, double y, double z ) : _x( x ), _y( y ), _z( z ) {}

    Point() = default;
};

struct Vector {
    double _x = 0;
    double _y = 0;
    double _z = 0;

    Vector( double x, double y, double z ) : _x( x ), _y( y ), _z( z ) {}

    Vector( const Point& start, const Point& finish ) : _x( finish._x - start._x ), _y( finish._y - start._y ),
                                                        _z( finish._z - start._z ) {}

    Vector operator+( const Vector& other ) {
        return Vector( this->_x + other._x, this->_y + other._y, this->_z + other._z );
    }

    Vector operator*( double c ) {
        return Vector( this->_x * c, this->_y * c, this->_z * c );
    }
};

double scalar_product( const Vector& v, const Vector& u ) {
    return ((u)._x * (v)._x + (u)._y * (v)._y + (u)._z * (v)._z);

}

double vector_product( const Vector& u, const Vector& v ) {
    double u_norn = scalar_product( u, u );
    double uXv = scalar_product( u, v );
    double v_norm = scalar_product( v, v );
    return u_norn * v_norm - uXv * uXv;
}

//void make_some_compares(){
//
//}

double dist_between_segments( const Point& p1, const Point& p2, const Point& r1, const Point& r2 ) {
    Vector u( p2, p1 );
    Vector v( r2, r1 );
    Vector w( p1, r1 );
    double u_norn = scalar_product( u, u );
    double uXv = scalar_product( u, v );
    double v_norm = scalar_product( v, v );
    double uXw = scalar_product( u, w );
    double vXw = scalar_product( v, w );
    double D = vector_product( u, v ); // vector product
    double s_c, t_c; // coefficients from 0 to 1, describing segments
    double s_normalised, t_normalised; // Normalized s and t - coordinates in sOt
    double sD = D; // s_c = s_normalised / sD, default sD = D >= 0
    double tD = D; // t_c = t_normalised / tD, default tD = D >= 0

    // compute the line parameters of the two closest points
    if (D < eps) { // the lines are almost parallel
        s_normalised = 0.0;         // force using point P0 on segment S1
        sD = 1.0;         // to prevent possible division by 0.0 later
        t_normalised = vXw;
        tD = v_norm;
    } else {
        // get the closest points on the infinite lines
        s_normalised = (uXv * vXw - v_norm * uXw);
        t_normalised = (u_norn * vXw - uXv * uXw);

        // sc<0 => the s=0 edge is visible
        if (s_normalised <= 0.0) {
            s_normalised = 0.0;
            t_normalised = vXw;
            tD = v_norm;
        } else if (s_normalised >= sD) {
            // sc>1  => the s=1 edge is visible
            s_normalised = sD;
            t_normalised = vXw + uXv;
            tD = v_norm;
        }
    }
    // tc<0 => the t=0 edge is visible
    if (t_normalised <= 0.0) {
        t_normalised = 0.0;

        if (-uXw <= 0.0)
            s_normalised = 0.0;
        else if (-uXw >= u_norn)
            s_normalised = sD;
        else {
            s_normalised = -uXw;
            sD = u_norn;
        }
    } else if (t_normalised >= tD) {
        // tc > 1  => the t=1 edge is visible
        t_normalised = tD;

        if ((-uXw + uXv) <= 0.0)
            s_normalised = 0;
        else if ((-uXw + uXv) >= u_norn)
            s_normalised = sD;
        else {
            s_normalised = (-uXw + uXv);
            sD = u_norn;
        }
    }

    s_c = (abs( s_normalised ) <= eps ? 0.0 : s_normalised / sD); // s_c = s_normalised / sD, default sD = D >= 0
    t_c = (abs( t_normalised ) <= eps ? 0.0 : t_normalised / tD); // t_c = t_normalised / tD, default tD = D >= 0

    // get the difference of the two closest points
    Vector dP = w + (u * s_c) + (v * t_c * (-1));  // =  S1(sc) - S2(tc)

    return sqrt( scalar_product( dP, dP ));   // return the closest distance
}

int main() {
    Point p1, p2, r1, r2;
    cin >> p1._x >> p1._y >> p1._z
        >> p2._x >> p2._y >> p2._z
        >> r1._x >> r1._y >> r1._z
        >> r2._x >> r2._y >> r2._z;

    cout << std::fixed;
    cout << setprecision( 10 );

    cout << dist_between_segments( p1, p2, r1, r2 );

    return 0;
}