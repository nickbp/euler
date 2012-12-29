/*
 * The sum of the squares of the first ten natural numbers is,
 * 1^2 + 2^2 + ... + 10^2 = 385
 *
 * The square of the sum of the first ten natural numbers is,
 * (1 + 2 + ... + 10)2 = 552 = 3025
 *
 * Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 − 385 = 2640.
 *
 * Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
 */

#include <stdint.h>
#include <stdio.h>

int main(void) {
    const int max = 100;
    uint64_t sum = (max + 1) * max / 2, sum_squares = 0;
    for (int i = 1; i <= max; ++i) {
        sum_squares += (i * i);
    }
    printf("sum_squares: %lu, square_sums: %lu, difference: %lu\n",
            sum_squares, sum * sum, (sum * sum) - sum_squares);
    return 0;
}
