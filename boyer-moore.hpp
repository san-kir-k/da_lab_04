#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "zfunc.hpp"

namespace BM {
    using TUll = unsigned long long;
    using TLl = long long;

    void BadSymPreprocess(  const std::vector<TUll>& pattern,
                            std::unordered_map<TUll, std::vector<TUll>>& symTable);
    void GoodSufPreprocess(const std::vector<TUll>& pattern, std::vector<TUll>& blVec, std::vector<TUll>& slVec);
    void NFunc(std::vector<TUll> pattern, std::vector<TUll>& nVec);
    // void LFunc();
    void BruteLFunc(const std::vector<TUll>& pattern, std::vector<TUll>& blVec, const std::vector<TUll>& nVec);
    void SmallLFunc(const std::vector<TUll>& pattern, std::vector<TUll>& slVec, const std::vector<TUll>& nVec);
    void Preprocess(const std::vector<TUll>& pattern,
                    std::unordered_map<TUll, std::vector<TUll>>& symTable,
                    std::vector<TUll>& blVec, 
                    std::vector<TUll>& slVec);
}