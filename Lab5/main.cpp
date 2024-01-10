#include <iostream>
#include <complex>
#define _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
import Math;
using namespace std;
int main()
{
    setlocale(LC_ALL, "ru");

    int choice;
    cout << "¬ведите 1, чтобы ввести модуль и аргумент комплексного числа, или 2, чтобы ввести действительную и мнимую части:";
    cin >> choice;

    Complex userComplex;

    if (choice == 1) {
        double mod, arg;
        cout << "¬ведите модуль: ";
        cin >> mod;
        cout << "¬ведите аргумент: ";
        cin >> arg;

        userComplex = Complex::FromExponentialForm(mod, arg);
    }
    else if (choice == 2) {
        double re, im;
        cout << "¬ведите действительную часть:";
        cin >> re;
        cout << "¬ведите мнимую часть: ";
        cin >> im;

        userComplex = Complex::FromAlgebraicForm(re, im);
    }
    else {
        cout << "Ќекорректный выбор" << endl;
        return 1;
    }

    cout << "¬ведите рациональное число в виде числитель/знаменатель: ";
    int nominator, denominator;
    char separator;
    cin >> nominator >> separator >> denominator;

    Rational userRational(nominator, denominator);

    double userDouble;
    cout << "¬ведите число: ";
    cin >> userDouble;

    cout << "f(" << userComplex << ") = " << f(userComplex) << endl;
    cout << "f(" << userRational << ") = " << f(userRational) << endl;
    cout << "f(" << userDouble << ") = " << f(userDouble) << endl;

    return 0;
}
