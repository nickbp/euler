/*
 * In the 20×20 grid below, four numbers along a diagonal line have been marked in red.
 *
 * <see 011-matrix.txt>
 *
 * The product of these numbers is 26 × 63 × 78 × 14 = 1788696.
 *
 * What is the greatest product of four adjacent numbers in the same direction (up, down, left, right, or diagonally) in the 20×20 grid?
 */

#include <stdio.h>
#include <string.h>

#include <fstream>
#include <vector>

typedef std::vector<int> line_t;
class Grid {
  public:
    void add_item(int val) {
        vals.back().push_back(val);
    }
    void add_row() {
        vals.push_back(line_t());
    }
    bool empty() const {
        return vals.empty();
    }
    void remove_last_row_if_empty() {
        if (!vals.empty() && vals.back().empty()) {
            vals.pop_back();
        }
    }

    int at(size_t row, size_t col) const {
        return vals[row][col];
    }
    size_t rows() const {
        return vals.size();
    }
    size_t cols() const {
        if (vals.empty()) {
            return 0;
        }
        return vals.front().size();
    }

  private:
    std::vector<line_t> vals;
};

#define LENGTH 4

static long greatest_product_at(const Grid &grid, const size_t row, const size_t col) {
    printf("r=%lu c=%lu (%d):\n", row, col, grid.at(row, col));
    long ret = 0;

    /* search to the right */
    if (col + LENGTH <= grid.cols()) {
        long right = 1;
        for (size_t i = 0; i < LENGTH; ++i) {
            right *= grid.at(row, col+i);
        }
        printf(" right=%ld\n", right);
        if (right > ret) {
            ret = right;
        }

        /* search diagonally right+down (\) */
        if (row + LENGTH <= grid.rows()) {
            long diagdn = 1;
            for (size_t i = 0; i < LENGTH; ++i) {
                diagdn *= grid.at(row+i, col+i);
            }
            printf(" diagdn=%ld\n", diagdn);
            if (diagdn > ret) {
                ret = diagdn;
            }
        }

        /* search diagonally right+up (/) */
        if (row >= LENGTH) {
            long diagup = 1;
            for (size_t i = 0; i < LENGTH; ++i) {
                diagup *= grid.at(row-i, col+i);
            }
            printf(" diagup=%ld\n", diagup);
            if (diagup > ret) {
                ret = diagup;
            }
        }
    }

    /* search down */
    if (row + LENGTH <= grid.rows()) {
        long down = 1;
        for (size_t i = 0; i < LENGTH; ++i) {
            down *= grid.at(row+i, col);
        }
        printf(" down=%ld\n", down);
        if (down > ret) {
            ret = down;
        }
    }

    printf("  result=%ld\n", ret);
    return ret;
}

static long find_greatest_product(const Grid &grid) {
    long ret = 0;
    /* we could run a rolling window in each direction,
       multiplying on the front and dividing on the back,
       but it wouldn't save us much time and would just be really complicated */
    for (size_t col = 0; col < grid.cols(); ++col) {
        for (size_t row = 0; row < grid.rows(); ++row) {
            long val_at_coords = greatest_product_at(grid, row, col);
            if (val_at_coords > ret) {
                ret = val_at_coords;
            }
        }
    }
    return ret;
}

int main(void) {
    std::ifstream ifs("011-matrix.txt");
    Grid grid;
    char buf[1024];
    while (ifs.good()) {
        memset(buf, 0, sizeof(buf));
        ifs.getline(buf, sizeof(buf));
        grid.add_row();
        size_t i_start = 0;
        for (size_t i_end = 0; i_end < sizeof(buf); ++i_end) {
            char c = buf[i_end];
            if (c == ',' || c == 0) {//comma or end of line
                if (i_start != i_end) {
                    //get int from i_start until i_end
                    size_t val = 0;
                    for (size_t i_digit = i_start; i_digit < i_end; ++i_digit) {
                        val *= 10;
                        val += buf[i_digit] - '0';
                    }
                    grid.add_item(val);
                    i_start = i_end+1;//start of next int (if any)
                }
                if (c == 0) {
                    break;//end of line
                }
            }
        }
        grid.remove_last_row_if_empty();
    }

    if (grid.empty()) {
        fprintf(stderr, "no data found, bye!");
        return -1;
    }
    printf("product: %ld\n", find_greatest_product(grid));
    return 0;
}
