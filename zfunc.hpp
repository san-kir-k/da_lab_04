#pragma once
#include <vector>
#include <algorithm>

namespace ZF {
    using TUll = unsigned long long;

    /*
     * Функция считает Z-функцию (Z(i) находит длину наибольшей подстроки, которая начинается в i
     * и совпадает с префиксом всей строки). Принимает на вход паттерн и вектор для результата.
     */
    void ZFunction(const std::vector<TUll>& pattern, std::vector<TUll>& zVec);
}
