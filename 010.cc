/*
 * The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
 *
 * Find the sum of all the primes below two million.
 */

#include <stdint.h>
#include <stdio.h>

#include <vector>

int main(void) {
    uint64_t prime_sum = 0;
    std::vector<bool> not_prime;
    not_prime.resize(2000000);
    /* sieve of eratosthenes, ripped from the wikipedia article pseudocode */
    for (uint64_t check = 2; check < not_prime.size(); ++check) {
        if (not_prime.size() > check && not_prime[check]) {
            /* okay, it's already marked nonprime, so continue.. */
            continue;
        }
        /* it looks prime! mark all multiples as non-prime */
        prime_sum += check;
        for (uint64_t check_mult = check*check; check_mult < not_prime.size(); check_mult += check) {
            not_prime[check_mult] = true;
        }
    }
    printf("sum: %lu\n", prime_sum);
    return 0;
}
