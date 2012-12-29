/*
 * In the 5 by 5 matrix below, the minimal path sum from the top left to the bottom right, by only moving to the right and down, is indicated in bold red and is equal to 2427.
 * [131]   673   234    103    18
 * [201]  [96]  [342]   965    150
 *  630    803  [746]  [422]   111
 *  537    699   497   [121]   956
 *  805    732   524   [37]   [331]
 *
 * Find the minimal path sum, in matrix.txt (right click and 'Save Link/Target As...'), a 31K text file containing a 80 by 80 matrix, from the top left to the bottom right by only moving right and down.
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

class Cache {
  public:
    Cache(const Grid& grid) {
        sums.resize(grid.rows());
        size_t cols = grid.cols();
        for (size_t i = 0; i < sums.size(); ++i) {
            sums[i].resize(cols, -1);
        }
    }

    void set(size_t row, size_t col, int val) {
        sums[row][col] = val;
    }
    bool get(size_t row, size_t col, int &val) const {
        int v = sums[row][col];
        if (v == -1) {
            return false;
        }
        val = v;
        return true;
    }

  private:
    std::vector<line_t> sums;
};

static int find_path(const Grid &grid, Cache &cache, size_t level = 0, size_t row = 0, size_t col = 0) {
    int ret = 0;
    if (cache.get(row, col, ret)) {
        /*for (size_t i = 0; i < level; ++i) {
            printf(" ");
        }
        printf("(cache) r=%lu, c=%lu: %d -> %d\n", row, col, grid.at(row, col), ret);*/
        return ret;
    }

    int cur = grid.at(row, col);
    /* recursion: DFS */
    if (row == grid.rows()-1) {
        /* at bottom edge */
        if (col == grid.cols()-1) {
            /* at right edge AND bottom edge: end! */
            ret = cur;
        } else {
            /* at bottom edge but NOT right edge: go right! */
            ret = cur + find_path(grid, cache, level+1, row, col+1);
        }
    } else if (col == grid.cols()-1) {
        /* at right edge but NOT bottom edge: go down! */
        ret = cur + find_path(grid, cache, level+1, row+1, col);
    } else {
        /* at neither right edge nor bottom edge: recurse and pick smallest! */
        int
            down = find_path(grid, cache, level+1, row+1, col),
            right = find_path(grid, cache, level+1, row, col+1);
        if (down < right) {
            ret = cur + down;
        } else {
            ret = cur + right;
        }
    }

    /*for (size_t i = 0; i < level; ++i) {
        printf(" ");
    }
    printf("r=%lu, c=%lu: %d -> %d\n", row, col, cur, ret);*/
    cache.set(row, col, ret);
    return ret;
}

int main(void) {
    std::ifstream ifs("081-matrix.txt");
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
    Cache cache(grid);
    printf("sum: %lu\n", find_path(grid, cache));
    return 0;
}
