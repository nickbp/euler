/*
 * A permutation is an ordered arrangement of objects. For example, 3124 is one
 * possible permutation of the digits 1, 2, 3 and 4. If all of the permutations
 * are listed numerically or alphabetically, we call it lexicographic order. The
 * lexicographic permutations of 0, 1 and 2 are:
 *
 *   012   021   102   120   201   210
 *
 * What is the millionth lexicographic permutation of the digits 0 thru 9?
 */

#include <stdio.h>
#include <string.h>

static void permute_repeat(const char digits[], char buf[], int len, int cur, int* printcount) {
    if (len == cur) {
        printf("%9d %s\n", ++(*printcount), buf);
        return;
    }
    int i = 0;
    for (; i < len; ++i) {
        if (*printcount > 1000000) {
            return;
        }
        buf[cur] = digits[i];
        permute_repeat(digits, buf, len, cur+1, printcount);
    }
}
static void permute_norepeat(const char digits[], char taken[], char buf[], int len, int cur, int* printcount) {
    if (len == cur) {
        int count = ++(*printcount);
        if (count % 10000 == 0) {
            printf("%9d %s\n", count, buf);
        }
        return;
    }
    int i = 0;
    for (; i < len; ++i) {
        if (*printcount > 1000000) {
            return;
        }
        if (taken[i]) {
            continue;
        }
        buf[cur] = digits[i];
        taken[i] = 1;
        permute_norepeat(digits, taken, buf, len, cur+1, printcount);
        taken[i] = 0;
    }
}

int main(void) {
    const char digits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    const int len = sizeof(digits)/sizeof(digits[0]);
    char buf[sizeof(digits)+1], taken[sizeof(digits)];
    memset(buf, 0, sizeof(digits)+1);//room for NUL
    memset(taken, 0, sizeof(digits));
    int count = 0;
    permute_norepeat(digits, taken, buf, len, 0, &count);
    /*count = 0;
      permute_repeat(digits, buf, len, 0, &count);*/
    return 0;
}
