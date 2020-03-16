/*
 * Change.cpp
 */

#include "Change.h"
#include <iostream>
#include <string>

string calcChange(int m, int numCoins, const int *coinValues)
{
    if (m == 0) return "";

    string res;

    unsigned minCoins[m+1];
    unsigned lastCoin[m+1];

    for (unsigned i = 0; i <= m; i++) {
        minCoins[i] = UINT32_MAX;
        lastCoin[i] = UINT32_MAX;
    }

    for (unsigned i = 1; i <= numCoins; i++) {  // i is the number of different coins we can use
        for (unsigned k = coinValues[i-1]; k <= m; k++) {     // k is the capacity of the backpack
            if (minCoins[k - coinValues[i - 1]] == UINT32_MAX) {
                if (k == coinValues[i-1]) {
                    minCoins[k] = 1;
                    lastCoin[k] = coinValues[i-1];
                }
            } else if ((coinValues[i-1] <= k) && (((1 + minCoins[k - coinValues[i-1]]) < minCoins[k]))) {
                minCoins[k] = 1 + minCoins[k - coinValues[i-1]];
                lastCoin[k] = coinValues[i-1];
            }
        }
    }

    if (minCoins[m] == UINT32_MAX) {
        return "-";
    } else {
        if (minCoins[m] == 0) {
            return "";
        } else {
            for (unsigned k  = m; k > 0; k -= lastCoin[k]) {
                res += to_string(lastCoin[k]) + ";";
            }
        }
    }

    return res;
}


