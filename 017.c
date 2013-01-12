/*
 * If the numbers 1 to 5 are written out in words: one, two, three, four, five,
 * then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
 *
 * If all the numbers from 1 to 1000 (one thousand) inclusive were written out
 * in words, how many letters would be used?
 *
 * NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and
 * forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20
 * letters. The use of "and" when writing out numbers is in compliance with
 * British usage.
 */

#include <stdint.h>
#include <stdio.h>

static int thousands(int *v) {
    if (*v >= 1000) {
        *v %= 1000;
        return 3 + 8;//one thousand
    }
    return 0;
}
static int hundreds(int *v) {
    int ret = 7;//hundred
    switch (*v / 100) {
        case 9:
            ret += 4;//nine
            break;
        case 8:
            ret += 5;//eight
            break;
        case 7:
            ret += 5;//seven
            break;
        case 6:
            ret += 3;//six
            break;
        case 5:
            ret += 4;//five
            break;
        case 4:
            ret += 4;//four
            break;
        case 3:
            ret += 5;//three
            break;
        case 2:
            ret += 3;//two
            break;
        case 1:
            ret += 3;//one
            break;
        case 0:
            return 0;
    }
    *v %= 100;
    return ret;
}
static int tens(int *v) {
    int ret = 0;
    switch (*v / 10) {
        case 9:
            ret = 6;//ninety
            break;
        case 8:
            ret = 6;//eighty
            break;
        case 7:
            ret = 7;//seventy
            break;
        case 6:
            ret = 5;//sixty
            break;
        case 5:
            ret = 5;//fifty
            break;
        case 4:
            ret = 5;//forty
            break;
        case 3:
            ret = 6;//thirty
            break;
        case 2:
            ret = 6;//twenty
            break;
        case 1:
            switch (*v) {
                case 19:
                    ret = 8;//nineteen
                    break;
                case 18:
                    ret = 8;//eighteen
                    break;
                case 17:
                    ret = 9;//seventeen
                    break;
                case 16:
                    ret = 7;//sixteen
                    break;
                case 15:
                    ret = 7;//fifteen
                    break;
                case 14:
                    ret = 8;//fourteen
                    break;
                case 13:
                    ret = 8;//thirteen
                    break;
                case 12:
                    ret = 6;//twelve
                    break;
                case 11:
                    ret = 6;//eleven
                    break;
                case 10:
                    ret = 3;//ten
                    break;
            }
            *v = 0;
            return ret;
        case 0:
            return 0;
    }
    *v %= 10;
    return ret;
}
static int ones(int *v) {
    int ret = 0;
    switch (*v) {
        case 9:
            ret = 4;//nine
            break;
        case 8:
            ret = 5;//eight
            break;
        case 7:
            ret = 5;//seven
            break;
        case 6:
            ret = 3;//six
            break;
        case 5:
            ret = 4;//five
            break;
        case 4:
            ret = 4;//four
            break;
        case 3:
            ret = 5;//three
            break;
        case 2:
            ret = 3;//two
            break;
        case 1:
            ret = 3;//one
            break;
        case 0:
            return 0;
    }
    *v = 0;
    return ret;
}

static int digitcount(int v) {
    const int v_orig = v;
    int ret = 0;
    if (v == 0) {
        ret += 4;//'zero'
    } else {
        ret += thousands(&v);
        ret += hundreds(&v);
        if (ret != 0 && v != 0) {
            ret += 3;//'and' (eg one thousand and five)
        }
        ret += tens(&v);
        ret += ones(&v);
    }
    printf("%d: %d\n", v_orig, ret);
    return ret;
}

int main(void) {
    digitcount(1000);
    digitcount(999);
    digitcount(342);
    digitcount(325);
    digitcount(300);
    digitcount(115);
    digitcount(99);
    digitcount(50);
    digitcount(19);
    digitcount(17);
    digitcount(10);
    digitcount(8);
    digitcount(4);
    digitcount(1);
    int sum = 0;
    for (int i = 1; i <= 1000; ++i) {
        sum += digitcount(i);
    }
    printf("sum 1,1000: %d\n", sum);
    return 0;
}
