/*
 * n! means n × (n − 1) × ... × 3 × 2 × 1
 *
 * For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
 * and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
 *
 * Find the sum of the digits in the number 100!
 */

#include <stdint.h>
#include <stdio.h>

#include <vector>

static void print(const std::vector<uint16_t> &digits) {
    int sum = 0;
    for (int i = digits.size()-1; i >= 0; --i) {
        printf("%d", (int)digits[i]);
        sum += digits[i];
    }
    printf(" (sum: %d)\n", sum);
}

int main(void) {
    const int exp = 100;
    std::vector<uint16_t> digits;//note: index 0 is the LAST digit

    digits.push_back(1);
    int carryover = 0;
    for (int n = 2; n <= exp; ++n) {
        for (int i = 0; i < digits.size(); ++i) {
            digits[i] *= n;
            if (carryover != 0) {
                digits[i] += carryover;
                carryover = 0;
            }
            if (digits[i] >= 10) {
                carryover = digits[i] / 10;
                digits[i] %= 10;
            }
        }
        while (carryover > 9) {
            digits.push_back(carryover % 10);
            carryover /= 10;
        }
        if (carryover != 0) {
            digits.push_back(carryover);
            carryover = 0;
        }
        printf("%d: ", n);
        print(digits);
    }
    return 0;
}
