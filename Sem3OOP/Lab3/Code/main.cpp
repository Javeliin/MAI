#include "figure.hpp"
#include <vector>


void Help() {
    std::cout << "Commands:\n+ - add figure\n\t+r - add rectangle\n\t" << 
        "+t - add triangle\n\t+s - add square\n- <id> - delete figure\n" <<
        "S <id> - figure area\nm <id> - figure median\np <id> - print figure\n" <<
        "h - help\nq - quit\n";
}

int main() {
    using data_type = int;

    char command;
    std::vector<Figure<data_type>*> figures;

    Help();
    while (true) {
        std::cin >> command;
        if (command == '+') {
            std::cin >> command;
            if (command == 'r') {
                Point<data_type> a, b, c, d;
                std::cin >> a >> b >> c >> d;
                try {
                    figures.push_back(
                        dynamic_cast<Figure<data_type>*>(new Rectangle<data_type>(a, b, c, d)));
                } catch(int) {
                    puts("Wrong coordinates. It is not rectangle.");
                }
            } else if (command == 't') {
                Point<data_type> a, b, c;
                std::cin >> a >> b >> c;
                try {
                    figures.push_back(
                        dynamic_cast<Figure<data_type>*>(new Triangle<data_type>(a, b, c)));
                } catch(int) {
                    puts("Wrong arguments. Not equaterial triangle.");
                }
            } else if (command == 's') {
                Point<data_type> a, b, c, d;
                std::cin >> a >> b >> c >> d;
                try {
                    figures.push_back(
                        dynamic_cast<Figure<data_type>*>(new Square<data_type>(a, b, c, d)));
                } catch(int) {
                    puts("Wrong arguments. It is not square.");
                }
            } else {
                puts("Wrong figure");
            }
        } else if (command == '-') {
            size_t id;
            std::cin >> id;
            if (id >= figures.size() || id < 0) {
                puts("Wrong id");
            } else {
                delete figures[id];
                figures.erase(figures.begin() + id);
                puts("Figure deleated");
            }
        } else if (command == 'S') {
            size_t id;
            std::cin >> id;
            if (id >= figures.size() || id < 0) {
                puts("Wrong id");
            } else {
                std::cout << "Area = " << figures[id]->GetArea() << '\n';
            }
        } else if (command == 'm') {
            size_t id;
            std::cin >> id;
            if (id >= figures.size() || id < 0) {
                puts("Wrong id");
            } else {
                std::cout << "Geometric median = " << figures[id]->GetMedian() << '\n';
            }
        } else if (command == 'p') {
            size_t id;
            std::cin >> id;
            if (id >= figures.size() || id < 0) {
                puts("Wrong id");
            } else {
                figures[id]->PrintFigure();
            }
        } else if (command == 'q' || command == EOF) {
            break;
        } else if (command == 'h') {
            Help();
        } else {
            puts("Wrong command. Try 'h' for help.");
        }
    }
    return 0;
}
