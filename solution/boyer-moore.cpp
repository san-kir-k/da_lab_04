#include "boyer-moore.hpp"
#include <iostream>

namespace BM {
    void BadSymPreprocess(  const std::vector<TLl>& pattern,
                            std::unordered_map<TLl, std::vector<TLl>>& symTable) {
        for (TLl i = pattern.size() - 1; i >= 0; --i) {
            symTable[pattern[i]].push_back(i);
        }
    }

    void NFunc(std::vector<TLl> pattern, std::vector<TLl>& nVec)  {
        std::reverse(pattern.begin(), pattern.end());
        std::vector<TLl> zVec;
        ZF::ZFunction(pattern, zVec);
        TLl n = pattern.size();
        for (TLl i = 0; i < n; ++i) {
            nVec.push_back(zVec[n - i - 1]);
        }
    }
    void BruteLFunc(const std::vector<TLl>& pattern, std::vector<TLl>& blVec, const std::vector<TLl>& nVec) {
        TLl n = pattern.size();
        for (TLl i = 0; i < n + 1; ++i) {
            blVec.push_back(0);
        }
        for (TLl j = 0; j < n - 1; ++j) {
            TLl i = n - nVec[j];
            blVec[i] = j;
        }
    }
    void SmallLFunc(const std::vector<TLl>& pattern, std::vector<TLl>& slVec, const std::vector<TLl>& nVec) {
        TLl n = pattern.size();
        for (TLl i = 0; i < n + 1; ++i) {
            slVec.push_back(0);
        }
        for (TLl i = n - 1; i >= 0; --i) {
            TLl j = n - 1 - i;
            if (nVec[j] == j + 1) {
                slVec[i] = j + 1;
            } else {
                slVec[i] = slVec[i + 1];
            }
        }
    }
    void GoodSufPreprocess(const std::vector<TLl>& pattern, std::vector<TLl>& blVec, std::vector<TLl>& slVec) {
        std::vector<TLl> nVec;
        NFunc(pattern, nVec);
        BruteLFunc(pattern, blVec, nVec);
        SmallLFunc(pattern, slVec, nVec);
    }

    void Preprocess(const std::vector<TLl>& pattern,
                    std::unordered_map<TLl, std::vector<TLl>>& symTable,
                    std::vector<TLl>& blVec, 
                    std::vector<TLl>& slVec) {
        BadSymPreprocess(pattern, symTable);
        GoodSufPreprocess(pattern, blVec, slVec);
    }

    void BoyerMoore(const std::vector<TLl>& text,
                    const std::vector<TLl>& pattern,
                    const std::vector<std::pair<TLl, TLl>>& newlines,
                    std::vector<std::pair<TLl, TLl>>& res) {
        std::unordered_map<TLl, std::vector<TLl>> symTable;
        std::vector<TLl> blVec;
        std::vector<TLl> slVec;
        Preprocess(pattern, symTable, blVec, slVec);
        TLl patternSize = pattern.size();
        TLl textSize = text.size();
        TLl shift = patternSize - 1;
        while (shift < textSize) {
            TLl i = patternSize - 1;
            TLl j = shift;
            while (j >= 0 && i >= 0 && pattern[i] == text[j]) {
                i--;
                j--;
            }
            if (i == -1) {
                TLl strNum = newlines[shift - patternSize + 1].first;
                TLl wordInStrNum = newlines[shift - patternSize + 1].second;
                res.push_back({strNum, wordInStrNum});
                if (patternSize == 1) {
                    shift++;
                } else {
                    shift += (patternSize - slVec[1]);
                }
            } else {
                TLl badSymVal = -1;
                for (auto v: symTable[text[j]]) {
                    if (i - v > 0) {
                        badSymVal = i - v;
                        break;
                    }
                }
                if (badSymVal == -1) {
                    badSymVal = patternSize;
                }
                TLl goodSufVal = -1;
                if (i + 1 == patternSize) {
                    goodSufVal = 1;
                } else {
                    TLl bruteLVal = blVec[i + 1];
                    TLl smallLVal = slVec[i + 1];
                    if (bruteLVal > 0) {
                        goodSufVal = patternSize - bruteLVal - 1;
                    } else {
                        goodSufVal = patternSize - smallLVal;
                    }
                }
                const TLl minShift = 1;
                shift += (std::max(std::max(goodSufVal, badSymVal), minShift));
            }
        }
    }
}
