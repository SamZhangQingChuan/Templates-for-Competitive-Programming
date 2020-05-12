#include "bits/stdc++.h"

int week(int y, int m, int d) {
    if (m < 3) {
        m += 12;
        y--;
    }
    int w = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    return w;
}

int main() {
    printf("%d\n", week(2015, 4, 16));  // => 3 Thursday
    printf("%d\n", week(1989, 2, 3));   // => 4 Friday
    return 0;
}

bool isLeap(int year) {
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

int getDays(int year, int month) {
    static int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeap(year) && month == 2)return 29;
    return days[month];
}


