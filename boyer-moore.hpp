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
    void GoodSufPreprocess();
    void NFunc(std::vector<TUll> pattern, std::vector<TUll>& nVec);
    // void LFunc();
    void BruteLFunc(std::vector<TUll>& pattern, std::vector<TUll>& blVec);
    void SmallLFunc(std::vector<TUll>& pattern, std::vector<TUll>& slVec);
    void Preprocess();
}