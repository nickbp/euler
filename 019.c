/*
 * You are given the following information, but you may prefer to do some research for yourself.
 *
 *  1 Jan 1900 was a Monday.
 *
 *  Thirty days has September,
 *  April, June and November.
 *  All the rest have thirty-one,
 *  Saving February alone,
 *  Which has twenty-eight, rain or shine.
 *  And on leap years, twenty-nine.
 *
 *  A leap year occurs on any year evenly divisible by 4,
 *  but not on a century unless it is divisible by 400.
 *
 * How many Sundays fell on the first of the month during the
 * twentieth century (1 Jan 1901 to 31 Dec 2000)?
 */

#include <assert.h>
#include <stdio.h>

static int num_days(int year, int month) {
    assert(year >= 0 && month >= 0 && month < 12);
    static size_t days[] = {
        31, 28, 31,// jan, feb, mar
        30, 31, 30,// apr, may, jun
        31, 31, 30,// jul, aug, sep
        31, 30, 31 // oct, nov, dec
    };
    if (month == 1 && year % 4 == 0) {//leap year is divisible by 4
        if (year % 100 != 0 || year % 400 == 0) {//not on a century, unless century is divisible by 400
            return 29;
        }
    }
    return days[month];
}
static const char* month_label(int month) {
    assert(month >= 0 && month < 12);
    static const char* labels[] = {
        "Jan", "Feb", "Mar",
        "Apr", "May", "Jun",
        "Jul", "Aug", "Sep",
        "Oct", "Nov", "Dec"
    };
    return labels[month];
}
static const char* day_label(int weekday) {
    assert(weekday >= 0 && weekday < 7);
    static const char* labels[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday", "Saturday"
    };
    return labels[weekday];
}

int main(void) {
    int first_sunday_count = 0;
    int cur_weekday = 1;//january 1, 1901 was a monday
    for (int year = 1900; year <= 2000; ++year) {
        for (int month = 0; month < 12; ++month) {
            printf("%s %d: %s\n", month_label(month), year, day_label(cur_weekday % 7));
            cur_weekday += num_days(year, month);
            if (cur_weekday % 7 == 0 && year >= 1901) {
                ++first_sunday_count;
            }
        }
    }
    printf("first sundays: %d\n", first_sunday_count);
    return 0;
}
