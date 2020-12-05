#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "zfunc.hpp"

using TLl = long long;
namespace BM {
    /*
     * Препроцессинг для расширенного правила плохого символа, которое накапливает
     * список вхождений символа в паттерн. Функция принимает паттерн и хэш-таблицу,
     * в которой ключ - символ, а значение  - вектор вхождений  
     */
    void BadSymPreprocess(  const std::vector<TLl>& pattern,
                            std::unordered_map<TLl, std::vector<TLl>>& symTable);
    /*
     * Препроцессинг для сильного правила хорошего суффикса, которое вычисляет функции l' и L'.
     * Функция принимает на вход паттерн и ссылки на векторы для вычесленых значений функций L' и l'.
     */
    void GoodSufPreprocess(const std::vector<TLl>& pattern, std::vector<TLl>& blVec, std::vector<TLl>& slVec);
    /*
     * Вычисляет N-функцию отзеркаленная Z-функция) для паттерна.
     * Функция принимает на вход паттерн и вектор-результат N-функции. 
     */ 
    void NFunc(std::vector<TLl> pattern, std::vector<TLl>& nVec);
    /* 
     * Вычисляет функцию L'. Функция L'(i) находит наибольшую позицию, меньшую n, такую, что P[i..n]
     * совпадает с суффиксом P[1..L'(i)] , а символ предшествующий этому суффиксу не равен P(i-1).
     * Функция принимает на вход паттерн, вектор-результат F' функции и посчитанный вектор-результат N-функции.
     */
    void BruteLFunc(const std::vector<TLl>& pattern, std::vector<TLl>& blVec, const std::vector<TLl>& nVec);
    /*
     * Вычисляет l' функцию. Функция l'(i) обозначает длину наибольшего суффикса P[i..n], который
     * является префиксом P. Если такого не существует, l'(i) == 0. Функция прнимает на вход
     * паттерн, вектор-результат f' функции и посчитанный вектор-результат N-функции.
     */
    void SmallLFunc(const std::vector<TLl>& pattern, std::vector<TLl>& slVec, const std::vector<TLl>& nVec);
    /*
     * Функция для объединения всех препроцессов. Принимает на вход паттерн, хэш-таблицу, 
     * в которой ключ - символ, а значение  - вектор вхождений, и ссылки на векторы для
     * вычесленых значений функций L' и l'.
     */
    void Preprocess(const std::vector<TLl>& pattern,
                    std::unordered_map<TLl, std::vector<TLl>>& symTable,
                    std::vector<TLl>& blVec, 
                    std::vector<TLl>& slVec);
    /*
     * Алгоритм Бойера-Мура для поиска подстроки в строке.
     * Принимает на вход текст, паттерн, вектор пар (в котором каждой позиции элемента сопоставляется
     * номер строки, в которой он находится, и порядковый номер в этой строке), результирующий вектор-ответ  
     */
    void BoyerMoore(const std::vector<TLl>& text,
                    const std::vector<TLl>& pattern,
                    const std::vector<std::pair<TLl, TLl>>& newlines,
                    std::vector<std::pair<TLl, TLl>>& res);
}
