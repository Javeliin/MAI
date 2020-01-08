#include "Figure.hpp"
#include "Factory.hpp"
#include <vector>
#include <stack>

using dataType = int;
using FiguresPair = std::pair<size_t, Figure<dataType>*>;

void Help() {
    std::cout << "Commands:\n+ - add figure\n\t+r - add rectangle\n\t" << 
        "+t - add triangle\n\t+s - add square\n- <id> - delete figure\n" <<
        "S <id> - figure area\nm <id> - figure median\np <id> - print figure\n" <<
        "h - help\nq - quit\n";
}

int main() {
    char command;

    std::vector<Figure<dataType>*> figures;
    std::stack<FiguresPair> figuresBuffer;

    Help();
    while (true) {
        size_t id = 0;
        size_t counter = 0;

        std::cin >> command;
        if (command == '+') {
            std::cin >> command;
            if (command == 'r') {
                figures.push_back(Factory<dataType>::CreateFigure(Factory<dataType>::Rec));
            } else if (command == 't') {
                figures.push_back(Factory<dataType>::CreateFigure(Factory<dataType>::Tri));
            } else if (command == 's') {
                figures.push_back(Factory<dataType>::CreateFigure(Factory<dataType>::Sqr));
            } else {
                puts("Wrong figure");
            }
            figuresBuffer.push(FiguresPair {counter++, nullptr});
        } else if (command == '-') {
            std::cin >> id;
            if (id >= figures.size() || id < 0) {
                puts("Wrong id");
            } else {
                figuresBuffer.push(std::pair<size_t, Figure<dataType>*>(id, figures[id]));
                delete figures[id];
                figures.erase(figures.begin() + id);
                puts("Figure deleated");
            }
        } else if (command == 'S') {
            std::cin >> id;
            if (id >= figures.size() || id < 0) {
                puts("Wrong id");
            } else {
                std::cout << "Area = " << figures[id]->GetArea() << '\n';
            }
        } else if (command == 'm') {
            std::cin >> id;
            if (id >= figures.size() || id < 0) {
                puts("Wrong id");
            } else {
                std::cout << "Geometric median = " << figures[id]->GetMedian() << '\n';
            }
        } else if (command == 'p') {
            std::cin >> id;
            if (id >= figures.size() || id < 0) {
                puts("Wrong id");
            } else {
                figures[id]->PrintFigure();
            }
        } else if (command == 'u') {
            if (figuresBuffer.size()) {
                FiguresPair tmp = figuresBuffer.top();
                if (tmp.second == nullptr) {
                    delete figures[id];
                    figures.erase(figures.begin() + id);
                } else {
                    figures.insert(figures.begin() + tmp.first, tmp.second);
                }
                figuresBuffer.pop();
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
