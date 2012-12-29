/*
 * Find the greatest product of five consecutive digits in the 1000-digit number:
 */

#define LONG_NUMBER \
    "73167176531330624919225119674426574742355349194934" \
    "96983520312774506326239578318016984801869478851843" \
    "85861560789112949495459501737958331952853208805511" \
    "12540698747158523863050715693290963295227443043557" \
    "66896648950445244523161731856403098711121722383113" \
    "62229893423380308135336276614282806444486645238749" \
    "30358907296290491560440772390713810515859307960866" \
    "70172427121883998797908792274921901699720888093776" \
    "65727333001053367881220235421809751254540594752243" \
    "52584907711670556013604839586446706324415722155397" \
    "53697817977846174064955149290862569321978468622482" \
    "83972241375657056057490261407972968652414535100474" \
    "82166370484403199890008895243450658541227588666881" \
    "16427171479924442928230863465674813919123162824586" \
    "17866458359124566529476545682848912883142607690042" \
    "24219022671055626321111109370544217506941658960408" \
    "07198403850962455444362981230987879927244284909188" \
    "84580156166097919133875499200524063689912560717606" \
    "05886116467109405077541002256983155200055935729725" \
    "71636269561882670428252483600823257530420752963450"

#include <string.h>
#include <stdio.h>

static inline int char_to_int(const char c) {
    return c - '0';
}

int main(void) {
    const size_t n_len = sizeof(LONG_NUMBER)/sizeof(char) - 1;//exclude NUL
    const size_t vals_len = 5;
    if (n_len < vals_len) {
        fprintf(stderr, "n_len < vals_len, bye\n");
        return -1;
    }

    const char* n = LONG_NUMBER;
    int vals[vals_len];/* circular queue of the divisors of vals_product_cur */
    int vals_product_cur = 1, vals_product_max = 0;

    /* initialize 'vals' stuff: */
    for (size_t i = 0; i < vals_len; ++i) {
        vals[i] = char_to_int(n[i]);
        vals_product_cur *= vals[i];
        //printf("%lu(%d): init cur %d\n", i, vals[i], vals_product_cur);
    }
    vals_product_max = vals_product_cur;

    /* perform the main search: */
    for (size_t i = vals_len; i < n_len; ++i) {
        size_t vals_idx = i % vals_len;
        if (vals[vals_idx] == 0) {
            /* we're removing a zero from our scan window.
               reset vals_product_cur from scratch, in case the zero's removal returns the product to a nonzero total */
            vals[vals_idx] = char_to_int(n[i]);
            vals_product_cur = 1;
            for (size_t i_v = 0; i_v < vals_len; ++i_v) {
                vals_product_cur *= vals[i_v];
            }
        } else {
            vals_product_cur /= vals[vals_idx];/* divide out the old val */
            vals[vals_idx] = char_to_int(n[i]);/* update the val */
            vals_product_cur *= vals[vals_idx];/* multiply in the new val */
        }
        //printf("%lu(%d): cur %d\n", i, vals[vals_idx], vals_product_cur);
        if (vals_product_cur > vals_product_max) {
            //printf(" NEW MAX\n");
            vals_product_max = vals_product_cur;
        }
    }
    printf("max: %d\n", vals_product_max);
    return 0;
}
