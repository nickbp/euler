/*
 * The prime factors of 13195 are 5, 7, 13 and 29.
 *
 * What is the largest prime factor of the number 600851475143 ?
 */

#include <math.h>
#include <stdint.h>

#include <iostream>
#include <vector>

static bool is_prime(std::vector<bool> &not_prime, const uint64_t check) {
    if (check < 2) {
        return false;
    }
    if (not_prime.size() <= check) {
        /* note that if we're growing the cache, we still need to start from scratch
           (eg catch all multiples of 2 within the new region) */
        not_prime.resize(check+1);
        /* sieve of eratosthenes, ripped from the wikipedia article pseudocode */
        for (uint64_t i = 2; i < not_prime.size(); ++i) {
            if (not_prime[i]) {
                /* okay, it's already marked nonprime, so continue.. */
                continue;
            }
            /* it looks prime! mark all multiples as non-prime */
            for (uint64_t i_mult = i*i; i_mult < not_prime.size(); i_mult += i) {
                not_prime[i_mult] = true;
            }
        }
    }
    return !not_prime[check];
}

static uint64_t largest_prime_divisor(const uint64_t val) {
    const uint64_t val_sqrt = sqrt(val);/* implicit floor */
    std::cout << "search within " << val_sqrt << std::endl;

    std::vector<bool> not_prime;
    for (uint64_t check = val_sqrt/*implicit floor*/; check > 0; --check) {
        if (val % check != 0) {
            /* this isn't a factor of val at all. skip! */
            continue;
        }
        std::cout << " factor: " << check << std::endl;
        /* okay, it's a factor of val, but is it a prime factor? */
        if (is_prime(not_prime, check)) {
            return check;
        }
    }
    return 0;
}

int main(void) {
    std::cout << "prime factor: " << largest_prime_divisor(13195) << std::endl;
    std::cout << "prime factor: " << largest_prime_divisor(600851475143) << std::endl;
    return 0;
}
