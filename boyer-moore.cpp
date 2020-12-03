#include "boyer-moore.hpp"
#include <iostream>

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
    void BruteLFunc(const std::vector<TUll>& pattern, std::vector<TUll>& blVec, const std::vector<TUll>& nVec) {
        TUll n = pattern.size();
        for (TUll i = 0; i < n; ++i) {
            blVec.push_back(0);
        }
        for (TUll j = 0; j < n - 1; ++j) {
            TUll i = n - nVec[j];
            blVec[i] = j;
        }
    }
    void SmallLFunc(const std::vector<TUll>& pattern, std::vector<TUll>& slVec, const std::vector<TUll>& nVec) {
        TUll n = pattern.size();
        for (TUll i = 0; i < n; ++i) {
            slVec.push_back(0);
        }
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
    void GoodSufPreprocess(const std::vector<TUll>& pattern, std::vector<TUll>& blVec, std::vector<TUll>& slVec) {
        std::vector<TUll> nVec;
        NFunc(pattern, nVec);
        BruteLFunc(pattern, blVec, nVec);
        SmallLFunc(pattern, slVec, nVec);
    }
    void Preprocess(const std::vector<TUll>& pattern,
                    std::unordered_map<TUll, std::vector<TUll>>& symTable,
                    std::vector<TUll>& blVec, 
                    std::vector<TUll>& slVec) {
        BadSymPreprocess(pattern, symTable);
        GoodSufPreprocess(pattern, blVec, slVec);
    }
    void BoyerMoore(const std::vector<TUll>& text,
                    const std::vector<TUll>& pattern,
                    const std::vector<TUll>& newlines,
                    std::vector<std::pair<TUll, TUll>>& res) {
        std::unordered_map<TUll, std::vector<TUll>> symTable;
        std::vector<TUll> blVec;
        std::vector<TUll> slVec;
        Preprocess(pattern, symTable, blVec, slVec);
        TUll n = pattern.size();
        TUll m = text.size();
        TUll k = n - 1;
        while (k < m) {
            TUll i = n - 1;
            TUll h = k;
            while (i >= 0 && pattern[i] == text[h]) {
                i--;
                h--;
            }
            if (i == -1) {
                TUll strNum = newlines[k - n + 1];
                TUll wordInStrNum = (k + 1 - n + 1) / strNum;
                res.push_back({strNum, wordInStrNum});
                k += n - slVec[1];
            } else {
                TLl bsVal = -1;
                for (auto v: symTable[text[k]]) {
                    if (i - v > 0) {
                        bsVal = i - v;
                        break;
                    }
                }
                if (bsVal == -1) {
                    bsVal = 1;
                }
                TLl gsVal = -1;
                if (i + 1 == n) {
                    gsVal = 1;
                } else {
                    TUll blVal = blVec[i + 1];
                    TUll slVal = slVec[i + 1];
                    if (blVal > 0) {
                        gsVal = n - blVal;
                    } else {
                        gsVal = n - slVal;
                    }
                }
                const TLl minK = 1;
                k += std::max(std::max(gsVal, bsVal), minK);
            }
            std::cout << "k: " << k << "\n";
        }
    }
}