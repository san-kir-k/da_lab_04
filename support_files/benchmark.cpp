#include <iostream>
#include <chrono>
#include <algorithm>
#include <string>
#include <vector>

#include "../solution/boyer-moore.hpp"
#include "../solution/zfunc.hpp"


using duration_t = std::chrono::microseconds;
const std::string DURATION_PREFIX = "us";
using TLl = long long;
using TUll = unsigned long;

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

/*
MacBook-Air-K:support_files AK$ ./wrapper.sh 
[info] [2020-12-05 13:53:34] Stage #1 Compiling...
g++ -std=c++17 -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic boyer-moore.o zfunc.o main.cpp -o solution
[info] [2020-12-05 13:53:35] Stage #2 Test generating...
[info] [2020-12-05 13:53:39] Stage #3 Checking...
[info] [2020-12-05 13:53:39] tests/test_1.t, lines=11 OK
[info] [2020-12-05 13:53:39] tests/test_2.t, lines=1001 OK
[info] [2020-12-05 13:53:39] tests/test_3.t, lines=10001 OK
[info] [2020-12-05 13:53:39] Stage #4 Benchmarking...
g++ -O2 -std=c++17 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic boyer-moore.o zfunc.o benchmark.cpp -o benchmark
[info] [2020-12-05 13:53:41] Running tests/test_1.t
Text length is 887
Pattern length is 28
Boyer-Moore time: 34us
Simple find time: 5us
[info] [2020-12-05 13:52:52] Running tests/test_2.t
Text length is 90357
Pattern length is 27
Boyer-Moore time: 394us
Simple find time: 890us
[info] [2020-12-05 13:53:41] Running tests/test_3.t
Text length is 893026
Pattern length is 22
Boyer-Moore time: 3873us
Simple find time: 5160us
*/

/*
5 0 1 0 4 6 6 5 0 7 0
1 1 5 0 1 0 4 6 6 5 0 7 0
*/