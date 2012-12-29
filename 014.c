/*
 * The following iterative sequence is defined for the set of positive integers:
 *
 * n → n/2 (n is even)
 * n → 3n + 1 (n is odd)
 *
 * Using the rule above and starting with 13, we generate the following sequence:
 * 13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
 *
 * It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms.
 * Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.
 *
 * Which starting number, under one million, produces the longest chain?
 *
 * NOTE: Once the chain starts the terms are allowed to go above one million.
 */

#include <stdio.h>

static int chainlength(const int v_orig) {
    long v = v_orig;
    int len = 1;
    while (v != 1) {
        //printf(" %ld\n", v);
        ++len;
        if (v % 2 == 0) {
            //printf("  even\n");
            v /= 2;
        } else {
            //printf("  odd\n");
            v *= 3;
            ++v;
        }
    }
    //printf("len=%d\n", len);
    return len;
}

int main() {
    int maxlen = 0, maxval = 0;
    for (int i = 1; i <= 1000000; ++i) {
        if (i % 100000 == 0) {
            printf("%d, max=%d\n", i, maxlen);
        }
        int len = chainlength(i);
        if (len > maxlen) {
            maxlen = len;
            maxval = i;
        }
    }
    printf("maxlen=%d @ val=%d\n", maxlen, maxval);
    return 0;
}
