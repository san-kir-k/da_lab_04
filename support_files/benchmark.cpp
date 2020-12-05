#include <iostream>
#include <chrono>
#include <algorithm>
#include <string>
#include <vector>

#include "../solution/boyer-moore.hpp"
#include "../solution/zfunc.hpp"


using duration_t = std::chrono::milliseconds;
const std::string DURATION_PREFIX = "ms";
using TLl = long long;

void Input(std::vector<TLl>& text, std::vector<TLl>& pattern, std::vector<std::pair<TLl, TLl>>& newlines) {
    std::string strPattern;
    std::string strText;
    std::getline(std::cin, strPattern);
    TLl nextWord = 0;
    bool isInit = false;
    TLl i = 0;
    while (i < strPattern.size() && strPattern[i] == ' ') {
        i++;
    }
    for (; i < strPattern.size(); ++i) {
        if (strPattern[i] == ' ' && isInit) {
            while (i < strPattern.size() && strPattern[i] == ' ') {
                i++;
            }
            pattern.push_back(nextWord);
            nextWord = 0;
            i--;
            isInit = false;
        } else {
            nextWord = nextWord * 10 + strPattern[i] - '0';
            isInit = true;
        }
    }
    if (isInit) {
        pattern.push_back(nextWord);
    }
    TLl lineCount = 1;
    while (getline(std::cin, strText)) {
        TLl nextWord = 0;
        TLl wordNum = 1;
        isInit = false;
        TLl i = 0;
        while (i < strText.size() && strText[i] == ' ') {
            i++;
        }
        for (; i < strText.size(); ++i) {
            if (strText[i] == ' ' && isInit) {
                while (i < strText.size() && strText[i] == ' ') {
                    i++;
                }
                text.push_back(nextWord);
                newlines.push_back({lineCount, wordNum}); 
                wordNum++;
                nextWord = 0;
                i--;
                isInit = false;
            } else {
                nextWord = nextWord * 10 + strText[i] - '0';
                isInit = true;
            }
        }
        if (isInit) {
            text.push_back(nextWord);  
            newlines.push_back({lineCount, wordNum}); 
        }
        lineCount++;     
    }
}

void SimpleFind(const std::vector<TLl>& text,
                const std::vector<TLl>& pattern,
                const std::vector<std::pair<TLl, TLl>>& newlines,
                std::vector<std::pair<TLl, TLl>>& res) {
    TLl i = 0;
    TLl j = 0;
    while (i < text.size()) {
        TLl h = i;
        while (h < text.size() && j < pattern.size() && text[h] == pattern[j]) {
            h++;
            j++;
        }
        if (j == pattern.size()) {
            TLl strNum = newlines[i].first;
            TLl wordInStrNum = newlines[i].second;
            res.push_back({strNum, wordInStrNum});            
        }
        j = 0;
        i++;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); 
    std::vector<TLl> pattern;
    std::vector<TLl> text;
    std::vector<std::pair<TLl, TLl>> newlines;
    Input(text, pattern, newlines);
    std::vector<std::pair<TLl, TLl>> res;

    std::cout << "Text length is " << text.size() << std::endl;
    std::cout << "Pattern length is " << pattern.size() << std::endl;
    // Измеряем время работы сортировки подсчётом.
    std::chrono::time_point<std::chrono::system_clock> start_ts = std::chrono::system_clock::now();
    BM::BoyerMoore(text, pattern, newlines, res);
    auto end_ts = std::chrono::system_clock::now();
    uint64_t bm_ts = std::chrono::duration_cast<duration_t>( end_ts - start_ts ).count();

    // Измеряем время работы stl сортировки.
    start_ts = std::chrono::system_clock::now();
    SimpleFind(text, pattern, newlines, res);
    end_ts = std::chrono::system_clock::now();
    uint64_t sf_ts = std::chrono::duration_cast<duration_t>( end_ts - start_ts ).count();

    std::cout << "Boyer-Moore time: " << bm_ts << DURATION_PREFIX << std::endl;
    std::cout << "Simple find time: " << sf_ts << DURATION_PREFIX << std::endl;
}