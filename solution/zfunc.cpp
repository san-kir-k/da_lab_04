#include "zfunc.hpp"
#include <iostream>

namespace ZF {
    void ZFunction(const std::vector<TLl>& pattern, std::vector<TLl>& zVec) {
        TLl n = pattern.size();
        for (TLl i = 0; i < n; ++i) {
            zVec.push_back(0);
        }
        TLl left = 0;
        TLl right = 0;
        for (TLl k = 1; k < n; ++k) {
            if (k > right) {
                TLl j = 0;
                TLl i = k;
                while (i < n && pattern[i] == pattern[j]) {
                    i++;
                    j++;
                }
                zVec[k] = j;
                if (zVec[k] > 0) {
                    right = k + zVec[k] - 1;
                    left = k;
                }
            } else {
                TLl matchingSuffixLen = right - k + 1;
                TLl kPrefix = k - left;
                if (zVec[kPrefix] < matchingSuffixLen) {
                    zVec[k] = zVec[kPrefix];
                } else {
                    TLl j = matchingSuffixLen;
                    TLl i = right + 1;
                    while (j < n && i < n && pattern[i] == pattern[j]) {
                        i++;
                        j++;
                    }
                    zVec[k] = i - k;
                    right = i - 1;
                    left = k;
                }
            }
        }
    }
}
