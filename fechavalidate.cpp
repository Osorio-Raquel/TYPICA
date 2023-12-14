bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool validateDate(const P& p) { // para la estructura
    int day, month, year;
    sscanf(p.f, "%d/%d/%d", &day, &month, &year);

    if (month < 1 || month > 12) {
        cout << "Error: Mes no válido." << endl;
        return false;
    }

    int daysInMonth;

    switch (month) {
        case 2:
            daysInMonth = isLeapYear(year) ? 29 : 28;
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

    if (day < 1 || day > daysInMonth) {
        cout << "Error: Día no válido para el mes ingresado." << endl;
        return false;
    }

    return true;
}