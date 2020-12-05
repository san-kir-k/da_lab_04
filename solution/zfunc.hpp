#pragma once
#include <vector>
#include <algorithm>

using TLl = long long;
namespace ZF {
    /*
     * Функция считает Z-функцию (Z(i) находит длину наибольшей подстроки, которая начинается в i
     * и совпадает с префиксом всей строки). Принимает на вход паттерн и вектор для результата.
     */
    void ZFunction(const std::vector<TLl>& pattern, std::vector<TLl>& zVec);
}
