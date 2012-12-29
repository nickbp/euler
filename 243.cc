/*
 * A positive fraction whose numerator is less than its denominator is called a proper fraction.
 * For any denominator, d, there will be d−1 proper fractions; for example, with d = 12:
 * 1/12 , 2/12 , 3/12 , 4/12 , 5/12 , 6/12 , 7/12 , 8/12 , 9/12 , 10/12 , 11/12.
 *
 * We shall call a fraction that cannot be cancelled down a resilient fraction.
 * Furthermore we shall define the resilience of a denominator, R(d), to be the ratio of its proper fractions that are resilient; for example, R(12) = 4/11.
 * In fact, d = 12 is the smallest denominator having a resilience R(d) < 4/10.
 *
 * Find the smallest denominator d, having a resilience R(d) < 15499/94744.
 */

#include <stdio.h>
#include <vector>

static size_t count_coprimes(size_t val, const std::vector<size_t> &prime_factors) {
    /* euler's totient function, from example on wikipedia */
    double count = val;
    for (std::vector<size_t>::const_iterator iter = prime_factors.begin();
         iter != prime_factors.end(); ++iter) {
        count *= (*iter - 1) / (double)*iter;
    }
    return count + 0.5;/* implicit floor, +.5 results in a rounding */
}

static size_t get_max_coprimes(const size_t val) {
    /* R(d) = count(resilient) / total = count(resilient) / (d-1)
     * R(d) < 15499 / 94744
     * count(coprime(x,d)) / (d-1) < 15499 / 94744
     * count(coprime(x,d)) < 15499 * (d-1) / 94744 */
    return 15499 * (val-1) / 94744.;/* implicit floor */
}

static bool fill_nonprimes(std::vector<bool> &not_prime, const int max) {
    not_prime.resize(max+1);
    /* sieve of eratosthenes, ripped from the wikipedia article pseudocode */
    for (int i = 2; i < not_prime.size(); ++i) {
        if (not_prime[i]) {
            /* okay, it's already marked nonprime, so continue.. */
            continue;
        }
        /* it looks prime! mark all multiples as non-prime */
        for (int i_mult = i*i; i_mult < not_prime.size(); i_mult += i) {
            not_prime[i_mult] = true;
        }
    }
}

static void try_permutations(size_t &smallest_fit, const std::vector<size_t> &primes_to_use, size_t cur_prime_i = 0, size_t accu_val = 1) {
    if (cur_prime_i == primes_to_use.size()) {
        /* we've consumed all the primes and we're apparently still under smallest_fit */
        printf("-> %lu\n", accu_val);
        size_t coprimes = count_coprimes(accu_val, primes_to_use);
        size_t max_coprimes = get_max_coprimes(accu_val);
        if (coprimes <= max_coprimes) {
            if (accu_val < smallest_fit) {
                printf("!! new best!: %lu coprimes, max %lu\n", accu_val, coprimes, max_coprimes);
                smallest_fit = accu_val;
            } else {
                printf("   fits, but exceeds best: %lu coprimes, max %lu\n", accu_val, coprimes, max_coprimes);
            }
        }
        return;
    }
    /* recurse with an additional prime: try all exponents that keep us under smallest_fit */
    for (size_t mult = 1; true; ++mult) {
        size_t accu_val_mult = accu_val;
        for (size_t i = 0; i < mult; ++i) {
            accu_val_mult *= primes_to_use[cur_prime_i];
        }
        if (accu_val_mult >= smallest_fit) {
            /* the value we've accumulated is already worse than our best. skip! */
            return;
        }
        try_permutations(smallest_fit, primes_to_use, cur_prime_i + 1, accu_val_mult);
    }
}

int main(void) {
    /*
      first off, a fraction is resilient if its numerator/denominator are relatively prime (aka coprime)
      so we need to find the first 'd' where the fraction of resilient fractions x/d (x < d) is < 15499/94744 (or < ~16.4%)
      to do this, we could just calculate gcd(x,d) for all x < d. if gcd=1, then coprime (and resilient fraction).
      but this would be inefficient -- a faster way would be to just construct a number with a lot of different primes in its decomposition. this number would have a very low resiliency relative to its value
    */

    std::vector<bool> not_prime_cache;
    fill_nonprimes(not_prime_cache, 10000);

    printf("get coprime counts of single-exponent prime products:\n");
    size_t accu_val = 1;
    std::vector<size_t> primes;
    for (size_t i = 2; i < not_prime_cache.size(); ++i) {
        if (not_prime_cache[i]) {
            /* not a prime, keep going */
            continue;
        }
        accu_val *= i;
        primes.push_back(i);
        size_t coprimes = count_coprimes(accu_val, primes);
        size_t max_coprimes = get_max_coprimes(accu_val);
        if (coprimes < max_coprimes) {
            /* we've found the first instance of a number which fits the max,
               but apparently this isn't the answer! consider this a max to search under. */
            printf("!! fits!: %lu (primes %lu...%lu): %lu coprimes, max %lu\n",
                    accu_val, primes.front(), primes.back(), coprimes, max_coprimes);
            primes.pop_back();
            break;
        } else {
            printf("%lu (primes %lu...%lu): %lu coprimes, max %lu\n", accu_val, primes.front(), primes.back(), coprimes, max_coprimes);
        }
    }

    /* at this point, accu_val has a value which fits under the max.
       but there's apparently another match which is less than accu_val (1*...*29),
       but likely greater than the previous accu_val (1*...*23).
       lets try some permutations with the primes preceding what we used to build accu_val,
       since presumably a small prime exponent will have what we want. */

    /* so lets try a bunch of permutations of the prime counts */
    printf("\nsearch permutations <%lu within primes %lu...%lu:\n", accu_val, primes.front(), primes.back());
    try_permutations(accu_val, primes);
    printf("found: %lu\n", accu_val);
    return 0;
}
