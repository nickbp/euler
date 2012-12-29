/*
 * By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
 *
 * What is the 10 001st prime number?
 */

#include <stdint.h>
#include <stdio.h>

#include <vector>

int main(void) {
    const int n = 10001;

    std::vector<uint64_t> primes;
    std::vector<bool> not_prime;
    not_prime.resize(250000);//arbitrarily large, must be grown to meet 'n'
    /* sieve of eratosthenes, ripped from the wikipedia article pseudocode */
    for (uint64_t check = 2; check < not_prime.size(); ++check) {
        if (not_prime.size() > check && not_prime[check]) {
            /* okay, it's already marked nonprime, so continue.. */
            continue;
        }
        /* it looks prime! mark all multiples as non-prime */
        primes.push_back(check);
        if (primes.size() == n) {
            break;
        }
        for (uint64_t check_mult = check*check; check_mult < not_prime.size(); check_mult += check) {
            not_prime[check_mult] = true;
        }
    }
    if (primes.empty()) {
        printf("no primes found\n");
    } else {
        printf("prime #%lu: %lu\n", primes.size(), primes.back());
    }
    return 0;
}
