#include <iostream>
#include <vector>

#include "zfunc.hpp"

using TUll = unsigned long long;

void Input(std::vector<TUll>& text, std::vector<TUll>& pattern, std::vector<TUll>& newlines) {
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
        for (int i = 0; i < strText.size(); ++i) {
            if (strText[i] == ' ') {
                while (strText[i] == ' ') {
                    i++;
                }
                i--;
                text.push_back(nextWord);
                newlines.push_back(lineCount); 
                nextWord = 0;
            } else {
                nextWord = nextWord * 10 + strText[i] - '0';
            }
        }
        text.push_back(nextWord);  
        newlines.push_back(lineCount); 
        lineCount++;     
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL); 
    std::vector<TUll> pattern;
    std::vector<TUll> text;
    std::vector<TUll> newlines;
    Input(text, pattern, newlines);
    
    return 0;
}