#include <iostream>
#include <vector>

#include "zfunc.hpp"
#include "boyer-moore.hpp"

using TUll = unsigned long long;

void Input(std::vector<TUll>& text, std::vector<TUll>& pattern, std::vector<std::pair<TUll, TUll>>& newlines) {
    std::string strPattern;
    std::string strText;
    std::getline(std::cin, strPattern);
    TUll nextWord = 0;
    for (int i = 0; i < strPattern.size(); ++i) {
        if (strPattern[i] == ' ') {
            while (strPattern[i] == ' ') {
                i++;
            }
            i--;
            pattern.push_back(nextWord);
            nextWord = 0;
        } else {
            nextWord = nextWord * 10 + strPattern[i] - '0';
        }
    }
    pattern.push_back(nextWord);
    TUll lineCount = 1;
    while (getline(std::cin, strText)) {
        TUll nextWord = 0;
        TUll wordNum = 1;
        for (int i = 0; i < strText.size(); ++i) {
            if (strText[i] == ' ') {
                while (strText[i] == ' ') {
                    i++;
                }
                i--;
                text.push_back(nextWord);
                newlines.push_back({lineCount, wordNum}); 
                wordNum++;
                nextWord = 0;
            } else {
                nextWord = nextWord * 10 + strText[i] - '0';
            }
        }
        text.push_back(nextWord);  
        newlines.push_back({lineCount, wordNum}); 
        lineCount++;     
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL); 
    std::vector<TUll> pattern;
    std::vector<TUll> text;
    std::vector<std::pair<TUll, TUll>> newlines;
    Input(text, pattern, newlines);
    std::vector<std::pair<TUll, TUll>> res;
    BM::BoyerMoore(text, pattern, newlines, res);
    for (auto p: res) {
        std::cout << p.first << ", " << p.second << "\n";
    }
    return 0;
}