#ifndef _FIGURE_H_
#define _FIGURE_H_

#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdexcept>


template <class T>
class Point : public std::pair<T, T> {
public:
    Point() : std::pair<T, T>() {
        this->first = 0;
        this->second = 0;
    }

    Point(T newFirst, T newSecond) : std::pair<T, T>() {
        this->first = newFirst;
        this->second = newSecond;
    }

    friend std::ostream& operator<< (std::ostream &out, const Point<T> &point) {
        out << std::fixed << std::setprecision(2) <<
            '(' << point.first << ',' << ' ' << point.second << ')';
        return out;
    }

    friend std::istream& operator>> (std::istream &in, Point<T> &point) {
        in >> point.first >> point.second;
        return in;
    }
};

template<class T>
double PointDistance(Point<T> a, Point<T> b) {
    return sqrt(pow(b.first - a.first, 2) + pow(b.second - a.second, 2));
}


template <class T>
class Figure {
public:
    virtual ~Figure() {}
};


template <class T>
class Triangle : public Figure<T> {
public:
    Point<T> A, B, C;

    Triangle() {}

    void Recreate(Point<T> a, Point<T> b, Point<T> c) {
        A = a;
        B = b;
        C = c;
    }
};


template <class T>
class Rectangle : public Figure<T> {
public:
    Point<T> A, B, C, D;

    Rectangle() {}

    void Recreate(Point<T> a, Point<T> b, Point<T> c, Point<T> d) {
        Point<T> vector1(b.first - a.first, b.second - a.second);
        Point<T> vector2(c.first - b.first, c.second - b.second);

        if (PointDistance(a, b) != PointDistance(c, d) || 
                vector1.first * vector2.first + 
                vector1.second * vector2.second != 0) {
            throw 0;
        }

        A = a;
        B = b;
        C = c;
        D = d;
    }
};


template <class T>
class Square : public Figure<T> {
public:
    Point<T> A, B, C, D;

    Square() {}

    void Recreate(Point<T> a, Point<T> b, Point<T> c, Point<T> d) {
        if (PointDistance(a, b) != PointDistance(b, c) || 
                PointDistance(a, b) != PointDistance(a, d) || 
                PointDistance(a, c) != PointDistance(b, d) ||
                PointDistance(a, b) != PointDistance(c, d)) {
            throw 0;
        }

        A = a;
        B = b;
        C = c;
        D = d;
    }
};

template <class T>
struct isTriangle {
    static const bool velue = false;
};

template <>
struct isTriangle<Triangle<double>> {
    static const bool velue = true;
};

template <>
struct isTriangle<Triangle<int>> {
    static const bool velue = true;
};

template <typename T>
constexpr bool isTuple = false;

template<typename ... types>
constexpr bool isTuple<std::tuple<types...>>   = true;

template <class T, 
        typename std::enable_if<isTriangle<T>::velue == true>::type* = nullptr>
Point<double> Median(T figure) {
    Point<double> median;
    median.first = (figure.A.first + figure.B.first + figure.C.first) / 3.0;
    median.second = (figure.A.second + figure.B.second + figure.C.second) / 3.0;
    return median;
}

template <class T,
        typename std::enable_if<isTriangle<T>::velue == false>::type* = nullptr>
Point<double> Median(T figure) {
    Point<double> median;
    median.first = (figure.A.first + figure.B.first + 
            figure.C.first + figure.D.first) / 4.0;
    median.second = (figure.A.second + figure.B.second + 
            figure.C.second + figure.D.second) / 4.0;
    return median;
}

template <class T, 
        typename  std::enable_if<isTuple<T>>::type* = nullptr>
Point<double> Median(T figure) {
    Point<double> median;
    median.first = (std::get<0>(figure).first + std::get<1>(figure).first +
            std::get<2>(figure).first) / 3.0;
    median.second = (std::get<0>(figure).second + std::get<1>(figure).second +
            std::get<2>(figure).second) / 3.0;
    return median;
}

template <class T, 
        typename std::enable_if<isTriangle<T>::velue == true>::type* = nullptr>
double Area(T figure) {
    double ab = PointDistance(figure.A, figure.B);
    double bc = PointDistance(figure.B, figure.C);
    double ac = PointDistance(figure.A, figure.C);
    double p = (ab + bc + ac) / 2.0;
    return sqrt(p * (p - ab) * (p - bc) * (p - ac));
}

template <class T, 
        typename std::enable_if<isTriangle<T>::velue == false>::type* = nullptr>
double Area(T figure) {
    return PointDistance(figure.A, figure.B) * PointDistance(figure.B, figure.C);
}

template <class T, 
        typename  std::enable_if<isTuple<T>>::type* = nullptr>
double Area(T figure) {
    double ab = PointDistance(std::get<0>(figure), std::get<1>(figure));
    double bc = PointDistance(std::get<1>(figure), std::get<2>(figure));
    double ac = PointDistance(std::get<0>(figure), std::get<2>(figure));
    double p = (ab + bc + ac) / 2.0;
    return sqrt(p * (p - ab) * (p - bc) * (p - ac));
}

template <class T, 
        typename std::enable_if<isTriangle<T>::velue == true>::type* = nullptr>
void PrintFigure(T figure) {
    std::cout << figure.A << '\t' << figure.B << '\t' << figure.C << '\n';
}

template <class T, 
        typename std::enable_if<isTriangle<T>::velue == false>::type* = nullptr>
void PrintFigure(T figure) {
    std::cout << figure.A << '\t' << figure.B << '\t' <<
            figure.C << '\t' << figure.D << '\n';
}

template <class T, 
        typename  std::enable_if<isTuple<T>>::type* = nullptr>
void PrintFigure(T figure) {
    std::cout << std::get<0>(figure) << '\t' << std::get<1>(figure) <<
            '\t' << std::get<2>(figure) << '\n';
}


#endif
