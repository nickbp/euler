/*
 * Euler published the remarkable quadratic formula:
 * n² + n + 41
 *
 * It turns out that the formula will produce 40 primes for the consecutive
 * values n = 0 to 39. However, when n = 40, 402 + 40 + 41 = 40(40 + 1) + 41 is
 * divisible by 41, and certainly when n = 41, 41² + 41 + 41 is clearly
 * divisible by 41.
 *
 * Using computers, the incredible formula  n² − 79n + 1601 was discovered,
 * which produces 80 primes for the consecutive values n = 0 to 79. The product
 * of the coefficients, −79 and 1601, is −126479.
 *
 * Considering quadratics of the form:
 *
 *  n² + an + b, where |a| < 1000 and |b| < 1000
 *
 *  where |n| is the modulus/absolute value of n
 *  e.g. |11| = 11 and |−4| = 4
 *
 * Find the product of the coefficients, a and b, for the quadratic expression
 * that produces the maximum number of primes for consecutive values of n,
 * starting with n = 0.
 */

#include <stdint.h>
#include <stdio.h>

#include <vector>

int main(void) {
    const int search_limit = 1000;/* if set to 2000, it finds a=-79, b=1601! yay! */

    std::vector<bool> not_prime;
    /* must be large enough to fit n^2 + search_limit*n + search_limit,
     * for n in the territory of <100: */
    not_prime.resize(2000000);
    /* sieve of eratosthenes, ripped from the wikipedia article pseudocode */
    for (uint64_t check = 2; check < not_prime.size(); ++check) {
        if (not_prime.size() > check && not_prime[check]) {
            /* okay, it's already marked nonprime, so continue.. */
            continue;
        }
        /* it looks prime! mark all multiples as non-prime */
        for (uint64_t check_mult = check*check; check_mult < not_prime.size(); check_mult += check) {
            not_prime[check_mult] = true;
        }
    }

    /* For the quadratic to be prime when n=0, then 'b' must be prime, since
     * f(0) = 0^2 + a0 + b = b. Therefore b is a prime from 2 thru 1000. */
    size_t best_n = 0;
    int best_a = 0, best_b = 0;
    for (int b = 2; b <= search_limit; ++b) {
        if (not_prime[b]) {
            continue;
        }
        /* Now for narrowing down 'a', lets try out n=1:
         * f(1) = 1 + a + b = prime, or >= 2. Therefore a >= 1 - b. */
        size_t count = 0;
        for (int a = 1 - b; a <= search_limit; ++a) {
            for (size_t n = 0; ; ++n) {
                int val = (n*n) + a*n + b;
                if (val < 0 || not_prime[val]) {
                    if (n > best_n) {
                        printf("a[%3d] b[%3d] -> %lu\n", a, b, n);
                        best_n = n;
                        best_a = a;
                        best_b = b;
                    }
                    break;
                }
            }
        }
    }
    printf("best: a[%3d] b[%3d] -> %lu\n", best_a, best_b, best_n);
    return 0;
}
