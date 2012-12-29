/*
 * Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
 *
 * <see 013-list.txt>
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <fstream>
#include <queue>
#include <vector>

class IntChunks {
  public:
    const static size_t CHUNKSZ = 10;

    IntChunks(const char *buf, size_t maxlen) {
        size_t len = strnlen(buf, maxlen);
        size_t chunk_start = 0, chunk_end = len;
        printf("full=%s\n", buf);
        for (;;) {
            if (chunk_end < CHUNKSZ) {
                chunk_start = 0;
            } else {
                chunk_start = chunk_end - CHUNKSZ;
            }
            size_t chunk_val = 0;
            for (size_t i = chunk_start; i < chunk_end; ++i) {
                chunk_val *= 10;
                chunk_val += buf[i] - '0';
            }
            printf("start=%lu, end=%lu, val=%lu\n",
                    chunk_start, chunk_end, chunk_val);
            vals.push(chunk_val);
            if (chunk_start == 0) {
                break;
            }
            chunk_end = chunk_start;
        }
    }

    int64_t Next() {
        /* produce least to greatest */
        int64_t ret = vals.front();
        vals.pop();
        return ret;
    }

    bool Empty() {
        return vals.empty();
    }

  private:
    std::queue<int64_t> vals;
};

static void print_sum_chunks(std::vector<IntChunks> &vals) {
    int64_t ret = 0;
    int64_t lastchunk_carryover = 0;

    int64_t chunk_divisor = 1;
    for (size_t i = 0; i < IntChunks::CHUNKSZ; ++i) {
        chunk_divisor *= 10;
    }
    printf("chunkdiv=%ld\n", chunk_divisor);

    while (!vals.front().Empty()) {
        int64_t chunk_sum = 0;
        for (std::vector<IntChunks>::iterator iter = vals.begin();
             iter != vals.end(); ++iter) {
            int64_t chunk = iter->Next();
            chunk_sum += chunk;
            //printf(" chunksum(%ld)=%ld\n", chunk, chunk_sum);
        }
        chunk_sum += lastchunk_carryover;
        //printf(" chunksum(co%ld)=%ld\n", lastchunk_carryover, chunk_sum);
        lastchunk_carryover = chunk_sum / chunk_divisor;
        printf("chunksum=%ld, carryover=%ld\n", chunk_sum, lastchunk_carryover);
    }
}

int main(void) {
    std::ifstream ifs("013-list.txt");
    std::vector<IntChunks> vals;
    char buf[1024];
    while (ifs.good()) {
        memset(buf, 0, sizeof(buf));
        ifs.getline(buf, sizeof(buf));
        if (ifs.good()) {
            vals.push_back(IntChunks(buf, sizeof(buf)));
        }
    }

    if (vals.empty()) {
        fprintf(stderr, "no data found, bye!");
        return -1;
    }
    print_sum_chunks(vals);
    return 0;
}
