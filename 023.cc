/*
 * A perfect number is a number for which the sum of its proper divisors is
 * exactly equal to the number. For example, the sum of the proper divisors of
 * 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.
 *
 * A number n is called deficient if the sum of its proper divisors is less than
 * n and it is called abundant if this sum exceeds n.
 *
 * As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest
 * number that can be written as the sum of two abundant numbers is 24. By
 * mathematical analysis, it can be shown that all integers greater than 28123
 * can be written as the sum of two abundant numbers. However, this upper limit
 * cannot be reduced any further by analysis even though it is known that the
 * greatest number that cannot be expressed as the sum of two abundant numbers
 * is less than this limit.
 *
 * Find the sum of all the positive integers which cannot be written as the sum
 * of two abundant numbers.
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>

#include <vector>

static void fill_abundants(std::vector<bool> &cache, unsigned int fill_thru) {
    cache.resize(fill_thru+1);// ensure fill_thru is itself included
    for (int val = 1; val < cache.size(); ++val) {
        int sum = 1;
        // test for all divisors of this number
        for (int i = 2; i <= sqrt(val); ++i) {
            if (val % i == 0) {
                if (i == val / i) {
                    sum += i;
                } else {
                    sum += i + (val / i);
                }
            }
        }
        if (sum > val) {
            cache[val] = true;
            printf("%d < %d\n", val, sum);
        }
    }
}

static bool has_abundant_sum(const std::vector<bool> &cache, unsigned int val) {
    assert(cache.size() > val);
    for (unsigned int i = 1; i <= val / 2; ++i) {
        if (cache[i] && cache[val - i]) {
            printf("%d: %d + %d\n", val, i, val - i);
            return true;
        }
    }
    printf("%d\n", val);
    return false;
}

int main(void) {
    std::vector<bool> abundants;
    fill_abundants(abundants, 30000);//MISSING: 196
    unsigned int sum = 0;
    for (unsigned int i = 1; i < abundants.size(); ++i) {
        if (!has_abundant_sum(abundants, i)) {
            sum += i;
        }
    }
    printf("sum: %u\n", sum);
    return 0;
}
