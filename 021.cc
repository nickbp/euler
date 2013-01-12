/*
 * Let d(n) be defined as the sum of proper divisors of n (numbers less than n
 * which divide evenly into n). If d(a) = b and d(b) = a, where a ≠ b, then a
 * and b are an amicable pair and each of a and b are called amicable numbers.
 *
 * For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44,
 * 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4,
 * 71 and 142; so d(284) = 220.
 *
 * Evaluate the sum of all the amicable numbers under 10000.
 */

#include <math.h>
#include <stdio.h>

#include <vector>

static void fill_divisor_sums(std::vector<int> &cache, unsigned int fill_thru) {
    cache.resize(fill_thru+1);// ensure fill_thru is itself included
    cache[0] = 0;
    for (int val = 1; val < cache.size(); ++val) {
        int sum = 1;
        // test for all divisors of this number
        for (int i = 2; i < sqrt(val); ++i) {
            if (val % i == 0) {
                // include eg both 4 and 71 for 284 (284 / 4 = 71)
                sum += i + (val / i);
            }
        }
        cache[val] = sum;
    }
}

int main(void) {
    std::vector<int> divisor_sums;//[val] = sum, thru fill_max
    fill_divisor_sums(divisor_sums, 10000);
    int sum_amicables = 0;
    for (int i = 0; i < divisor_sums.size(); ++i) {
        int i_divisors = divisor_sums[i];
        // tiebreaker to avoid duplicates: only look if the other val is smaller than we are
        if (i_divisors < divisor_sums.size() && i_divisors < i) {
            int other_divisors = divisor_sums[i_divisors];
            if (other_divisors == i) {
                printf("%d, %d\n", i, i_divisors);
                sum_amicables += i + i_divisors;
            }
        }
    }
    printf("sum: %d\n", sum_amicables);
    return 0;
}
