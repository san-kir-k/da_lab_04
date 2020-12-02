#include "zfunc.hpp"

namespace ZF {
    void ZFunction(const std::vector<TUll>& pattern, std::vector<TUll>& zVec) {
        for (TUll i = 0; i < pattern.size(); ++i) {
            zVec.push_back(0);
        }
        TUll left = 0;
        TUll right = 0;
        for (TUll k = 1; k < pattern.size(); ++k) {
            if (k > right) {
                TUll j = 0;
                TUll i = k;
                while (pattern[i] == pattern[j]) {
                    i++;
                    j++;
                }
                zVec[k] = j;
                if (zVec[k] > 0) {
                    right = k + zVec[k] - 1;
                    left = k;
                }
            } else {
                TUll matchingSuffixLen = right - k + 1;
                TUll kPrefix = k - left;
                if (zVec[kPrefix] < matchingSuffixLen) {
                    zVec[k] = zVec[kPrefix];
                } else {
                    TUll j = matchingSuffixLen;
                    TUll i = right + 1;
                    while (pattern[i] == pattern[j]) {
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