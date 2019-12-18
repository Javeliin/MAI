/*Дата: 17.09.19
Автор: Андреев Игорь Анатольевич
Группа: M8O-207Б-18
Вариант: 1
Представление комплексных чисел в арифметическом виде
Реализация операции сравнения модулей комплексных чисел, сложения, вычитания, умножения, деления, сравнения с помощью перегрузки операторов, нахождение сопряженного
Изучить механизмы работы литералов*/

#include <cmath>
#include <stdio.h>
#include <string>


class Complex {
private:
    double real, imag;
public:
    Complex(double newReal = 0, double newImag = 0) {
        real = newReal;
        imag = newImag;
    }

    Complex set_value(double newReal, double newImag) {
        real = newReal;
        imag = newImag;
        return *this;
    }

    double get_imag() {
        return imag;
    }

    double get_real() {
        return real;
    }

    Complex& operator=(Complex a) {
        if (*this == a) {
            return *this;
        }
        real = a.real;
        imag = a.imag;
        return *this;
    }

    Complex operator+(Complex a) {
        Complex out;
        out.real = real + a.real;
        out.imag = imag + a.imag;
        return out;
    }

    Complex operator-(Complex a) {
        Complex out;
        out.real = real - a.real;
        out.imag = imag - a.imag;
        return out;
    }

    Complex operator*(Complex a) {
        Complex out;
        out.real = a.real * real - a.imag * imag;
        out.imag = a.imag * real + a.real * imag;
        return out;
    }

    Complex conj() {
        Complex out;
        out.imag = -imag;
        return out;
    }

    Complex operator/(Complex a) {
        Complex out;
        Complex tmp = a * a.conj();
        if (tmp.get_imag() == 0 && tmp.get_real() == 0) {
            throw 10;
        }
        out.real = (real * a.real + imag * a.imag) / (a.real * a.real + a.imag * a.imag);
        out.imag = (imag * a.real - real * a.imag) / (a.real * a.real + a.imag * a.imag);
        return out;
    }

    bool operator==(Complex a) {
        return (real == a.real) && (imag == a.imag) ? true : false;
    }
};

bool sign(char c) {
    return (c == '+' || c == '-' || c == ' ' || c == 'i') ? true : false;
}

Complex operator"" _comp(const char* num, size_t size) {
    Complex tmp;
    std::string s = (std::string)num;
    long long unsigned int i = 0;
    int j = 1;
    double real = 0;
    double imag = 0;
    if (s[i] == '-') {
        ++i;
        while (s[i] != '.') {
            real = 10*real - (s[i] - '0');
            ++i;
            if (i == s.size()) {
                return tmp.set_value(real, 0);
            }
        }
        ++i;
        while (!sign(s[i])) {
            real -= (s[i] - '0') / (pow(10, j));
            ++j;
            ++i;
            if (i == s.size()) {
                return tmp.set_value(real, 0);
            }
        }
    } else {
        while (s[i] != '.') {
            real = 10*real + (s[i] - '0');
            ++i;
            if (i == s.size()) {
                return tmp.set_value(real, 0);
            }
        }
        ++i;
        while (!sign(s[i])) {
            real += (s[i] - '0') / (pow(10, j));
            ++j;
            ++i;
            if (i == s.size()) {
                return tmp.set_value(real, 0);
            }
        }
    }

    if (s[i] == 'i') {
        return tmp.set_value(0, real);
    }

    while (sign(num[i])) {
        if (num[i] == '-') {
            imag = 1;
        }
        ++i;
    }

    j = 1;
    if (imag == 1) {
        imag = 0;
        while (s[i] != '.') {
            imag = 10*imag - (s[i] - '0');
            ++i;
        }
        ++i;
        while (!sign(s[i]) && i != s.size()) {
            imag -= (s[i] - '0') / (pow(10, j));
            ++j;
            ++i;
        }
    } else {
        while (s[i] != '.') {
            imag = 10*imag + (s[i] - '0');
            ++i;
        }
        ++i;
        while (!sign(s[i]) && i != s.size()) {
            imag += (s[i] - '0') / (pow(10, j));
            ++j;
            ++i;
        }
    }
    return tmp.set_value(real, imag);
}

void print(Complex a) {
    double real = a.get_real();
    double imag = a.get_imag();

    if (real == 0) {
        if (imag == 0) {
            printf("0\n");
        } else {
            printf("%.3lfi\n", imag);
        }
    } else {
        if (imag > 0) {
            printf("%.3lf+%.3lfi\n", real, imag);
        } else if (imag == 0) {
            printf("%.3lf\n", real);
        } else {
            printf("%.3lf%.3lf\n", real, imag);
        }
    }
}

double modulo(Complex a) {
    return pow((pow(a.get_real(), 2) + pow(a.get_imag(), 2)), 0.5);
}

int main() {
    Complex first, second, result;

    first = "124.23 + 998.43i"_comp;
    second = "212.54-323.0i"_comp;

    result = first + second;
    printf("Sum: ");
    print(result);

    result = first - second;
    printf("Sub: ");
    print(result);

    result = first * second;
    printf("Mult: ");
    print(result);

    try {
        result = first / second;
        printf("Div: ");
        print(result);
    } catch (int a){
        printf("Divided by 0\n");
    }

    first == second ? printf("Equal\n") : printf("Not equal\n");

    modulo(first) == modulo(second) ? printf("Mods equal\n") :
            printf("Mods not equal\n");
    return 0;
}
