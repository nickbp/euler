/*
 * A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.
 *
 * Find the largest palindrome made from the product of two 3-digit numbers.
 */

#include <stdio.h>

static int is_palindrome_impl(int check, int digit_count) {
    if (digit_count == 1) {
        /* base case A: single digit */
        return 1;
    }
    if (digit_count == 2) {
        /* base case B: two digits, which match if the number is a multiple of 11 (11 thru 99) */
        return (check % 11 == 0) ? 1 : 0;
    }

    /* recursion: check that the first and last digit match, then recurse on the middle. */
    int first_digit = check, last_digit = check % 10, first_digit_val = 1;
    for (int digits_left = digit_count-1; digits_left > 0; --digits_left) {
        first_digit /= 10;
        first_digit_val *= 10;
    }
    first_digit_val *= first_digit;/* if 'check' is 9876, 'first_digit_val' is now 9000 */
    if (first_digit != last_digit) {
        /* first and last digits dont match, so not a palindrome */
        return 0;
    }
    /* the first and last digits match, so lets try the digits in the middle */
    int remainder = (check - first_digit_val) / 10;
    return is_palindrome_impl(remainder, digit_count - 2);
}

static int is_palindrome(int check) {
    if (check < 0) {
        return 0;
    }

    int check_counter = check;
    int digit_count = 0;
    while (check_counter > 0) {
        check_counter /= 10;
        ++digit_count;
    }
    return is_palindrome_impl(check, digit_count);
}

int main(void) {
    int largest = 0;
    const int min = 100, max = 999;
    for (int i = max; i >= min; --i) {
        for (int j = max; j >= min; --j) {
            int check = i*j;
            if (largest >= check) {
                /* skip: we've already found a better palindrome! */
                continue;
            }
            if (is_palindrome(check)) {
                printf("found: %d (%d * %d)\n", check, i, j);
                largest = check;
            }
        }
    }
    printf("LARGEST: %d\n", largest);
    return 0;
}
