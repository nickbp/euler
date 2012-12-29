/*
 * Starting in the top left corner of a 2×2 grid, there are 6 routes (without backtracking) to the bottom right corner.
 *
 * How many routes are there through a 20×20 grid?
 */

#include <stdio.h>

static void bincoeff(int k) {/* largely ripped from wikipedia python example */
    const int n = 2 * k;//n+k, where n == k
    long ret = 1;
    for (int i = 1; i < k+1; ++i) {
        ret *= n - (k - i);
        ret /= i;
    }
    printf("bincoeff(%d) = %ld\n", k, ret);
}

int main() {
    /* navigating through the grid is always n+n moves (so a 2x2 grid has 4 moves)
       each of those moves is either downward or across. if we think of the
       across moves as +0 and the downward moves as +1, then any valid path
       needs to ultimately add up to n.

       for example, on the 2x2 grid, a valid move is:
       across(+0), down(+1), across(+0), down(+1) = +2

       so we need to find out the number of valid permutations of (0,1) which
       add up to n, given n+n moves.

       this sounds like a job for the binomial coefficient!
       wikipedia sez: "there are (n+k k) strings containing k ones and n zeros"
       for us, n = k, so it's effectively (2k k), where k is the grid width/height.
       so we just need to calculate that and we'll be all set! */
    bincoeff(1);
    bincoeff(2);
    bincoeff(3);
    bincoeff(20);//this one
    return 0;
}
