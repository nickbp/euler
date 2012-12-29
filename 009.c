/*
 * A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
 * a^2 + b^2 = c^2
 *
 * For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.
 *
 * There exists exactly one Pythagorean triplet for which a + b + c = 1000.
 * Find the product a * b * c.
 */

#include <string.h>
#include <stdio.h>

static inline int pow2(int in) {
    return in * in;
}

int main(void) {
    /*
      given:
      0 < a < b < c
      a^2 + b^2 = c^2
      a+b+c = 1000

      derivations:
      c = 1000-a-b, c^2 = (1000-a-b)^2 = a^2 + b^2
      so this at least brings us down to an O(n^2) search,
      with additional shortcuts possible on the ranges to be searched (eg b > a, a+b < 1000)
    */
    int a_found = 0, b_found = 0;
    for (int a_test = 1/*a > 0*/; a_test < 1000; ++a_test) {
        int asquared = pow2(a_test);
        for (int b_test = a_test + 1/*b > a*/; b_test < (1000 - a_test)/*a+b < 1000*/; ++b_test) {
            if (pow2(1000 - a_test - b_test) == (asquared + pow2(b_test))) {
                a_found = a_test;
                b_found = b_test;
                break;
            }
        }
        if (a_found != 0) {
            break;
        }
    }
    if (a_found == 0) {
        fprintf(stderr, "nothing found for a and b!\n");
        return -1;
    }
    int c_found = 1000 - a_found - b_found;
    printf("found: a=%d, b=%d, c=%d\n", a_found, b_found, c_found);
    printf("a*b*c: %d\n", a_found * b_found * c_found);
    return 0;
}
