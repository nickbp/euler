/*
 * If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
 *
 * Find the sum of all the multiples of 3 or 5 below 1000.
 */

#include <stdio.h>

int main(void) {
    /* lets just get all multiples directly */
    unsigned int sum = 0;
    /* all multiples of 3 */
    printf("3:\n");
    for (int i = 3; i < 1000; i += 3) {
        sum += i;
        printf("%.3d -> %d\n", i, sum);
    }
    /* all multiples of 5, except ones which are also multiples of 3
     * these skipped numbers are the multiples of 15, but lets keep things simple */
    printf("5:\n");
    for (int i = 5; i < 1000; i += 5) {
        if (i % 3 != 0) {
            sum += i;
            printf("%.3d -> %d\n", i, sum);
        } else {
            printf("%.3d -> skip\n", i);
        }
    }
    printf("sum: %u\n", sum);
    return 0;
}
