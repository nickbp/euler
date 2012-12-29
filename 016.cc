/*
 * 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
 *
 * What is the sum of the digits of the number 2^1000?
 */

#include <stdint.h>
#include <stdio.h>

#include <vector>

static void print(const std::vector<char> &digits) {
    int sum = 0;
    for (int i = digits.size()-1; i >= 0; --i) {
        printf("%d", (int)digits[i]);
        sum += digits[i];
    }
    printf(" (sum: %d)\n", sum);
}

int main(void) {
    const int exp = 1000;
    std::vector<char> digits;//note: index 0 is the LAST digit

    digits.push_back(1);
    int carryover = 0;
    for (int n = 0; n < exp; ++n) {
        for (int i = 0; i < digits.size(); ++i) {
            digits[i] *= 2;
            if (carryover != 0) {
                digits[i] += carryover;
                carryover = 0;
            }
            if (digits[i] >= 10) {
                carryover = digits[i] / 10;
                digits[i] %= 10;
            }
        }
        if (carryover != 0) {
            digits.push_back(carryover);
            carryover = 0;
        }
        printf("%d: ", n+1);
        print(digits);
    }
    return 0;
}
