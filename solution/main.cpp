#include <iostream>
#include <vector>

#include "boyer-moore.hpp"

using TLl = long long;

// обработчик ввода
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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); 
    std::vector<TLl> pattern;
    std::vector<TLl> text;
    std::vector<std::pair<TLl, TLl>> newlines;
    Input(text, pattern, newlines);
    std::vector<std::pair<TLl, TLl>> res;
    BM::BoyerMoore(text, pattern, newlines, res);
    for (auto p: res) {
        std::cout << p.first << ", " << p.second << "\n";
    }
    return 0;
}
