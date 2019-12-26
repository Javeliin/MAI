#ifndef _FIGURE_H_
#define _FIGURE_H_

#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdexcept>


template<class T>
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


template<class T>
class Figure {
public:
    virtual void PrintFigure() {}

    virtual double GetArea() {
        return 0;
    }

    virtual Point<double> GetMedian() {
        return Point<double>();
    }

    virtual ~Figure() {}
};


template<class T>
class Triangle : public Figure<T> {
public:
    Triangle(Point<T> a, Point<T> b, Point<T> c) {
        A = a;
        B = b;
        C = c;
    }

    void PrintFigure() {
        std::cout << A << '\t' << B << '\t' << C << '\n';
    }

    double GetArea() {
        return (pow(PointDistance(A, B), 2) * sqrt(3)) / 4.0;
    }

    Point<double> GetMedian() {
        Point<double> median;
        median.first = (A.first + B.first + C.first) / 3.0;
        median.second = (A.second + B.second + C.second) / 3.0;
        return median;
    }

private:
    Point<T> A, B, C;
};


template<class T>
class Rectangle : public Figure<T> {
public:
    Rectangle(Point<T> a, Point<T> b, Point<T> c, Point<T> d) {
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

    void PrintFigure() {
        std::cout << A << '\t' << B << '\t' << C << '\t' << D << '\n';
    }
    
    double GetArea() {
        return PointDistance(A, B) * PointDistance(B, C);
    }

    Point<double> GetMedian() {
        Point<double> median;
        median.first = (A.first + B.first + C.first + D.first) / 4.0;
        median.second = (A.second + B.second + C.second + D.second) / 4.0;
        return median;
    }

private:
    Point<T> A, B, C, D;
};


template<class T>
class Square : public Figure<T> {
public:
    Square(Point<T> a, Point<T> b, Point<T> c, Point<T> d) {
        if (PointDistance(a, b) != PointDistance(b, c) || 
                PointDistance(a, b) != PointDistance(a, d) || 
                PointDistance(a, b) != PointDistance(c, d)) {
            throw 0;
        }

        A = a;
        B = b;
        C = c;
        D = d;
    }

    void PrintFigure() {
        std::cout << A << '\t' << B << '\t' << C << '\t' << D << '\n';
    }

    double GetArea() {
        return pow(PointDistance(A, B), 2);
    }

    Point<double> GetMedian()    {
        Point<double> median;
        median.first = (A.first + B.first + C.first + D.first) / 4.0;
        median.second = (A.second + B.second + C.second + D.second) / 4.0;
        return median;
    }

private:
    Point<T> A, B, C, D;
};

#endif
