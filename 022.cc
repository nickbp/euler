/*
 * Using 022-names.txt, a 46K text file containing over five-thousand first
 * names, begin by sorting it into alphabetical order. Then working out the
 * alphabetical value for each name, multiply this value by its alphabetical
 * position in the list to obtain a name score.
 *
 * For example, when the list is sorted into alphabetical order, COLIN, which is
 * worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN
 * would obtain a score of 938 × 53 = 49714.
 *
 * What is the total of all the name scores in the file?
 */

#include <string.h>

#include <fstream>
#include <set>
#include <vector>

int main(void) {
    std::ifstream ifs("022-names.txt");
    std::set<std::string> sorted_names;
    char buf[1024];
    while (ifs.good()) {
        memset(buf, 0, sizeof(buf));
        ifs.getline(buf, sizeof(buf), ',');
        size_t len = strnlen(buf, sizeof(buf));
        if (len < 2) {
            continue;
        }
        std::string quotes_stripped(buf+1, len-2);
        //printf("%s -> %s\n", buf, quotes_stripped.c_str());
        sorted_names.insert(quotes_stripped);
    }
    size_t sum_scores = 0;
    size_t offset = 1;//position starts at 1 (no 0th name)
    for (std::set<std::string>::const_iterator iter = sorted_names.begin();
         iter != sorted_names.end(); ++iter) {
        size_t char_score = 0;
        const std::string &name = *iter;
        for (size_t i = 0; i < name.size(); ++i) {
            char_score += name[i] - 'A' + 1;//'A' gets a score of 1
        }
        const size_t total_score = char_score * offset;
        printf("%lu %s -> %lu\n", offset, iter->c_str(), total_score);
        sum_scores += total_score;
        ++offset;
    }
    printf("Total: %lu\n", sum_scores);
    return 0;
}
