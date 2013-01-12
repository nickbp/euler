/*
 * The Fibonacci sequence is defined by the recurrence relation:
 *
 *  Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.
 *
 * Hence the first 12 terms will be:
 *
 *  F1 = 1
 *  F2 = 1
 *  F3 = 2
 *  F4 = 3
 *  F5 = 5
 *  F6 = 8
 *  F7 = 13
 *  F8 = 21
 *  F9 = 34
 *  F10 = 55
 *  F11 = 89
 *  F12 = 144
 *
 * The 12th term, F12, is the first term to contain three digits.
 *
 * What is the first term in the Fibonacci sequence to contain 1000 digits?
 */

#include <stdio.h>

#include <vector>

typedef std::vector<char> bignum_t;//note: index 0 is the LAST digit

static void print(const bignum_t &digits) {
    for (int i = digits.size()-1; i >= 0; --i) {
        printf("%d", (int)digits[i]);
    }
}

static int sum(bignum_t &a_out, const bignum_t &b) {
    char carryover = 0;
    /*print(a_out);
    printf(" + ");
    print(b);*/
    for (int i = 0; i < a_out.size() || i < b.size(); ++i) {
        char digit_sum = carryover;
        if (i < a_out.size()) {
            digit_sum += a_out[i];
        }
        if (i < b.size()) {
            digit_sum += b[i];
        }
        if (i < a_out.size()) {
            a_out[i] = digit_sum % 10;
        } else {
            a_out.push_back(digit_sum % 10);
        }
        carryover = digit_sum / 10;
    }
    if (carryover != 0) {
        a_out.push_back(carryover);
    }
    /*printf(" = ");
    print(a_out);
    printf("\n");*/
    return a_out.size();
}

int main(void) {
    bignum_t a, b;
    a.push_back(1);
    b.push_back(1);
    const int maxlen = 1000;
    for (int count = 3; ; ++count) {//line up to '12th term is 114'
        int len = (count % 2 == 1) ? sum(b, a) : sum(a, b);
        if (len == maxlen) {
            printf("%d: ", count);
            if (count % 2 == 1) {
                print(b);
            } else {
                print(a);
            }
            printf("\n");
            break;
        }
    }
    return 0;
}
