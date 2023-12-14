#include <iostream>
#include <sstream>

using namespace std;

struct Date {
    int day, month, year;
};

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool validateDate(const string& a) {
    Date date;

    istringstream b(a);
    char d;

    b >> date.day >> d >> date.month >> d >> date.year;

    if (b.fail() || b.bad()) {
        cout << "Formato no valido." << endl;
        return false;
    }

    int daysInMonth;

    if (date.month < 1 || date.month > 12) {
        cout << "Mes no valido" << endl;
        return false;
    }

    switch (date.month) {
        case 2:
            daysInMonth = isLeapYear(date.year) ? 29 : 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            daysInMonth = 30;
            break;
        default:
            daysInMonth = 31;
            break;
    }

    if (date.day < 1 || date.day > daysInMonth) {
        cout << "Dia no valido para el mes ingresado" << endl;
        return false;
    }

    return true;
}

int main() {
    string a = "45/05/2023";

    if (validateDate(a)) {
        cout << "Fecha valida" << endl;
    } else {
        cout << "Fecha no valida" << endl;
    }

    return 0;
}
