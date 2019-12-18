#include "figure.hpp"
#include <vector>
#include <string>


void Help() {
    std::cout << "Commands:\n+ - add figure\n\t+r - add rectangle\n\t" << 
        "+t - add triangle\n\t+s - add square\n- <id> - delete figure\n" <<
        "S <id> - figure area\nm <id> - figure median\np <id> - print figure\n" <<
        "h - help\nq - quit\n";
}

int main() {
    using data_type = int;

    std::string command;
    char figureType;

    Triangle<data_type> triangle;
    Rectangle<data_type> rectangle;
    Square<data_type> square;
    std::tuple<Point<data_type>, Point<data_type>, Point<data_type>> trTuple;

    Help();
    while (true) {
        std::cin >> command;
        if (command == "new") {
            std::cin >> command;
            if (command == "rect") {
                Point<data_type> a, b, c, d;
                std::cin >> a >> b >> c >> d;
                try {
                    rectangle.Recreate(a, b, c, d);
                    figureType = 'r';
                } catch(...) {
                    puts("Wrong coordinates. It is not rectangle.");
                }
            } else if (command == "tri") {
                Point<data_type> a, b, c;
                std::cin >> a >> b >> c;
                try {
                    triangle.Recreate(a, b, c);
                    figureType = 't';
                } catch(...) {
                    puts("Wrong arguments. Not triangle.");
                }
            } else if (command == "square") {
                Point<data_type> a, b, c, d;
                std::cin >> a >> b >> c >> d;
                try {
                    square.Recreate(a, b, c, d);
                    figureType = 's';
                } catch(...) {
                    puts("Wrong arguments. It is not square.");
                }
            } else if (command == "tuple") {
                Point<data_type> a, b, c;
                std::cin >> a >> b >> c;
                try {
                    
                }
            } else {
                puts("Wrong figure");
            }
        } else if (command == "area") {
            if (figureType == 'r') {
                std::cout << Area(rectangle) << '\n';
            } else if (figureType == 't') {
                std::cout << Area(triangle) << '\n';
            } else if (figureType == 's') {
                std::cout << Area(square) << '\n';
            }
        } else if (command == "median") {
            if (figureType == 'r') {
                std::cout << Median(rectangle) << '\n';
            } else if (figureType == 't') {
                std::cout << Median(triangle) << '\n';
            } else if (figureType == 's') {
                std::cout << Median(square) << '\n';
            }
        } else if (command == "print") {
            if (figureType == 'r') {
                PrintFigure(rectangle);
            } else if (figureType == 't') {
                PrintFigure(triangle);
            } else if (figureType == 's') {
                PrintFigure(square);
            }
        } else if (command == "help") {
            Help();
        } else if (command == "quit") {
            break;
        } else {
            puts("Wrong command. Try \"help\" for help.");
        }
    }
    return 0;
}
