#ifndef _FACTORY_H_
#define _FACTORY_H_

#include "Figure.hpp"


template <class T>
class Factory {
public:
    enum FigureType {
        Rec,
        Tri,
        Sqr
    };

    static Figure<T>* CreateFigure(FigureType figure) {
        if (figure == Rec) {
            Point<T> a, b, c, d;
            std::cin >> a >> b >> c >> d;
            return dynamic_cast<Figure<T>*>(new Rectangle<T>(a, b, c, d));
        } else if (figure == Tri) {
            Point<T> a, b, c;
            std::cin >> a >> b >> c;
            return dynamic_cast<Figure<T>*>(new Triangle<T>(a, b, c));
        } else if (figure == Sqr) {
            Point<T> a, b, c, d;
            std::cin >> a >> b >> c >> d;
            return dynamic_cast<Figure<T>*>(new Square<T>(a, b, c, d));
        }
        puts("Wrong figure");
        return nullptr;
    }
};

#endif