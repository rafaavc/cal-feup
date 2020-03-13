/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>
#include <vector>

string calcSum(int * sequence, int size)
{
    unsigned in_sum = 0;
    vector<unsigned> sums;
    vector<unsigned> pair;
    vector<vector<unsigned>> pairs;
    for (unsigned m = 1; m <= size; m++) {
        for (auto it = sums.begin(); it != sums.end(); it++) {
            sums.erase(it);
            it--;
        }
        for (unsigned i = 0; i < size; i++) {
            in_sum = 0;
            if (i + m <= size) {
                for (unsigned k = 0; k < m; k++) {
                    in_sum += sequence[i + k];
                }
            } else {
                break;
            }
            sums.push_back(in_sum);
        }

        for (auto it = pair.begin(); it != pair.end(); it++) {
            pair.erase(it);
            it--;
        }
        for (unsigned i = 0; i < sums.size(); i++) {
            if (pair.empty()) {
                pair.push_back(sums[i]);
                pair.push_back(i);
            } else {
                if (sums.at(i) < pair.at(0)) {
                    pair.at(0) = sums.at(i);
                    pair.at(1) = i;
                }
            }
        }
        pairs.push_back(pair);
    }
    string res = "";
    for (unsigned i = 0; i < pairs.size(); i++) {
        res += to_string(pairs.at(i).at(0)) + "," + to_string(pairs.at(i).at(1)) + ";";
    }

	return res;
}

