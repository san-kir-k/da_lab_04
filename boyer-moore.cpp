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
                    const std::vector<std::pair<TUll, TUll>>& newlines,
                    std::vector<std::pair<TUll, TUll>>& res) {
        std::unordered_map<TUll, std::vector<TUll>> symTable;
        std::vector<TUll> blVec;
        std::vector<TUll> slVec;
        Preprocess(pattern, symTable, blVec, slVec);
        TUll patternSize = pattern.size();
        TUll textSize = text.size();
        TUll shift = patternSize - 1;
        while (shift < textSize) {
            TUll i = patternSize - 1;
            TUll j = shift;
            while (i >= 0 && pattern[i] == text[j]) {
                i--;
                j--;
            }
            if (i == -1) {
                TUll strNum = newlines[shift - patternSize + 1].first;
                TUll wordInStrNum = newlines[shift - patternSize + 1].second;
                res.push_back({strNum, wordInStrNum});
                shift += patternSize - slVec[1];
            } else {
                TLl badSymVal = -1;
                for (auto v: symTable[text[shift]]) {
                    if (i - v > 0) {
                        badSymVal = i - v;
                        break;
                    }
                }
                if (badSymVal == -1) {
                    badSymVal = 1;
                }
                TLl goodSufVal = -1;
                if (i + 1 == patternSize) {
                    goodSufVal = 1;
                } else {
                    TUll bruteLVal = blVec[i + 1];
                    TUll smallLVal = slVec[i + 1];
                    if (bruteLVal > 0) {
                        goodSufVal = patternSize - bruteLVal;
                    } else {
                        goodSufVal = patternSize - smallLVal;
                    }
                }
                const TLl minShift = 1;
                shift += std::max(std::max(goodSufVal, badSymVal), minShift);
            }
        }
    }
}
