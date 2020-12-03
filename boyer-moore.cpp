#include "boyer-moore.hpp"

namespace BM {
    void BadSymPreprocess(  const std::vector<TUll>& pattern,
                            std::unordered_map<TUll, std::vector<TUll>>& symTable) {
        for (TLl i = pattern.size() - 1; i >= 0; --i) {
            symTable[pattern[i]].push_back(i);
        }
    }
    void NFunc(std::vector<TUll> pattern, std::vector<TUll>& nVec)  {
        std::reverse(pattern.begin(), pattern.end());
        std::vector<TUll> zVec;
        ZF::ZFunction(pattern, zVec);
        TUll n = pattern.size();
        for (TUll i = 0; i < n; ++i) {
            nVec.push_back(zVec[n - i - 1]);
        }
    }
    // void LFunc();
    void BruteLFunc(std::vector<TUll>& pattern, std::vector<TUll>& blVec) {
        TUll n = pattern.size();
        for (TUll i = 0; i < n; ++i) {
            blVec.push_back(0);
        }
        std::vector<TUll> nVec;
        NFunc(pattern, nVec);
        for (TUll j = 0; j < n - 1; ++j) {
            TUll i = n - nVec[j];
            blVec[i] = j;
        }
    }
    void SmallLFunc(std::vector<TUll>& pattern, std::vector<TUll>& slVec) {
        TUll n = pattern.size();
        for (TUll i = 0; i < n; ++i) {
            slVec.push_back(0);
        }
        std::vector<TUll> nVec;
        NFunc(pattern, nVec);
        for (TLl i = n - 1; i >= 0; --i) {
            TUll j = n - i - 1;
            if (nVec[j] == j + 1) {
                slVec[i] = j + 1;
            } else {
                if (i + 1 <= n - 1) {
                    slVec[i] = slVec[i + 1];
                }
            }
        }
    }
    void GoodSufPreprocess();
    void Preprocess();
}