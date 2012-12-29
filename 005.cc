/*
 * 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
 *
 * What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
 */

#include <iostream>
#include <vector>

static bool is_prime(std::vector<bool> &not_prime, const int check) {
    if (check < 2) {
        return false;
    }
    if (not_prime.size() <= check) {
        /* note that if we're growing the cache, we still need to start from scratch
           (eg catch all multiples of 2 within the new region) */
        not_prime.resize(check+1);
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
    return !not_prime[check];
}

void get_prime_factors(int val, std::vector<bool> &not_prime_cache, std::vector<int> &counts) {
    const int val_orig = val;
    /* repeatedly divide val by primes until there's nothing left. */
    counts.resize(val+1);
    for (int i = 2; i <= val_orig; ++i) {
        if (!is_prime(not_prime_cache, i)) {/* slightly inefficient: not_prime_cache repeatedly regenerated as i grows */
            continue;
        }
        while (val % i == 0) {
            //std::cout << i << std::endl;
            val /= i;
            ++counts[i];
        }
        if (val == 0) {
            break;
        }
    }
    std::cout << val_orig << ":";
    for (size_t i = 0; i < counts.size(); ++i) {
        if (counts[i] > 0) {
            std::cout << " " << i << ":" << counts[i];
        }
    }
    std::cout << std::endl;
}

int main(void) {
    /* use prime factorization to get the lcm
     *
     * 20: 2^2 * 5
     * 19: 19
     * 18: 2 * 3^2
     * 17: 17
     * 16: 2^4
     * 15: 3 * 5
     * 14: 2 * 7
     * 13: 13
     * 12: 2^2 * 3
     * 11: 11
     * 10: 2 * 5
     * 9: 3^2
     * 8: 2^3
     * 7: 7
     * 6: 2 * 3
     * 5: 5
     * 4: 2^2
     * 3: 3
     * 2: 2
     *
     * lcm(2:20) = 2^4 * 3^2 * 5 * 7 * 11 * 13 * 17 * 19
     *           = 16 * 9 * 5 * 7 * 11 * 13 * 17 * 19
     *           = 232,792,560
     */
    std::cout << "hey its 232792560" << std::endl;

    /* and now a code version of what the above does by hand: */
    const int start = 20;
    std::vector<int> largest_factor_counts;
    largest_factor_counts.resize(start);

    std::vector<bool> not_prime_cache;
    /* go from largest to smallest so that not_prime_cache isn't repeatedly rebuilt: */
    for (int n = start; n >= 2; --n) {
        std::vector<int> factor_counts;
        get_prime_factors(n, not_prime_cache, factor_counts);
        for (size_t fc = 0; fc < factor_counts.size(); ++fc) {
            if (factor_counts[fc] > largest_factor_counts[fc]) {
                largest_factor_counts[fc] = factor_counts[fc];
            }
        }
    }

    unsigned long lcm = 1;
    for (size_t lfc = 0; lfc < largest_factor_counts.size(); ++lfc) {
        //std::cout << lfc << ": " << largest_factor_counts[lfc] << std::endl;
        for (size_t lfc_pow = 0; lfc_pow < largest_factor_counts[lfc]; ++lfc_pow) {
            lcm *= lfc;
        }
    }
    std::cout << "yep its " << lcm << std::endl;
    return 0;
}
