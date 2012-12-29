/*
 * By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.
 *
 * [3]
 * [7]  4
 *  2  [4]  6
 *  8   5  [9]  3
 *
 * That is, 3 + 7 + 4 + 9 = 23.
 *
 * Find the maximum total from top to bottom of the triangle below:
 *
 * <see 018-list.txt>
 *
 * NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route.
 * However, Problem 67, is the same challenge with a triangle containing one-hundred rows; it cannot be solved by brute force, and requires a clever method! ;o)
 */

#include <string.h>
#include <stdio.h>

#include <fstream>
#include <vector>

class Tree {
  public:
    void Add(int val) {
        size_t cur_level_max_size = levels.size();
        if (cur_level_max_size == 0 ||/*avoid levels.back() against empty vector*/
                levels.back().size() == cur_level_max_size) {
            /* cur level is full (eg level 2 has 2 elements): add new level */
            levels.push_back(level_t());
        }

        levels.back().push_back(NodeVal(val));
        //Print();
    }

    int MaxSum() {
        return max_sum_imp(0, 0);
    }

    void Print() const {
        printf("%lu levels:\n", levels.size());
        for (std::vector<level_t>::const_iterator level = levels.begin();
             level != levels.end(); ++level) {
            for (level_t::const_iterator val = level->begin();
                 val != level->end(); ++val) {
                printf("%2d ", val->Value());
            }
            printf("\n");
        }
        printf("\n");
    }

  private:
    class NodeVal {
      public:
        NodeVal(int val)
        : val(val), max_sum(-1) { }

        int Value() const {
            return val;
        }

        bool Max(int &max) const {
            if (max_sum == -1) {
                return false;
            }
            max = max_sum;
            return true;
        }

        void SetMax(int max) {
            max_sum = max;
        }

      private:
        int val;//would be const, but vector dislikes that
        int max_sum;/* the max sum of the child tree rooted at this node,
                       including this node's val */
    };
    typedef std::vector<NodeVal> level_t;

    int max_sum_imp(size_t level_idx, size_t offset) {
        if (level_idx >= levels.size()) {
            /* base case: we've extended beyond the end of the tree */
            return 0;
        }
        level_t &level = levels[level_idx];
        if (offset >= level.size()) {
            /* another base case (nice to have): we've extendned beyond the end of this level */
            return 0;
        }

        /* recursive case: return max of the child tree rooted at this node */

        NodeVal &val = level[offset];
        int max = 0;
        {
            /* check cache */
            if (val.Max(max)) {
                return max;
            }
        }

        /* calculate/fill cache: recurse */

        /* left: increment level_idx, leave offset the same (go down vertically) */
        int left_max = max_sum_imp(level_idx + 1, offset);
        /* right: increment both level_idx and offset (go down diagonally to the right) */
        int right_max = max_sum_imp(level_idx + 1, offset + 1);

        max = level[offset].Value() + ((left_max > right_max) ? left_max : right_max);
        val.SetMax(max);/* fill cache */
        return max;
    }

    std::vector<level_t> levels;
};

static bool read_tree(std::ifstream &in, Tree &tree) {
    if (!in.good()) {
        return false;
    }
    char buf[1024];
    while (in.good()) {
        memset(buf, 0, sizeof(buf));
        in.getline(buf, sizeof(buf));
        if (in.good()) {
            size_t i_start = 0;
            for (size_t i_end = 0; i_end < sizeof(buf); ++i_end) {
                char c = buf[i_end];
                if (c == ' ' || c == 0) {//space or end of line
                    if (i_start != i_end) {
                        //get int from i_start until i_end
                        size_t val = 0;
                        for (size_t i_digit = i_start; i_digit < i_end; ++i_digit) {
                            val *= 10;
                            val += buf[i_digit] - '0';
                        }
                        tree.Add(val);
                        i_start = i_end+1;//start of next int (if any)
                    }
                    if (c == 0) {
                        break;//end of line
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    /*
    {
        Tree tree;
        tree.Add(3);

        tree.Add(7);
        tree.Add(4);

        tree.Add(2);
        tree.Add(4);
        tree.Add(6);

        tree.Add(8);
        tree.Add(5);
        tree.Add(9);
        tree.Add(3);

        tree.Print();

        printf("max: %d\n", tree.MaxSum());
    }
    */

    {
        std::ifstream ifs("018-list.txt");
        Tree tree;
        if (!read_tree(ifs, tree)) {
            return -1;
        }
        tree.Print();
        printf("max: %d\n", tree.MaxSum());
    }

    {
        std::ifstream ifs("067-list.txt");
        Tree tree;
        if (!read_tree(ifs, tree)) {
            return -1;
        }
        tree.Print();
        printf("max: %d\n", tree.MaxSum());
    }

    return 0;
}
