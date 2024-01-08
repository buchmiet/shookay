#include "pch.h"
#include "StringConverter.h"
#include <cwctype>
#include <chrono>
#include <iostream>
#include <set>
#include "UtfConv.h"
#include <algorithm>

std::string StringConverter::ConvertUTF8(const char* data, int length) {
    return std::string(data, length);
}

std::u16string StringConverter::ConvertUTF16(const char* data, int length) {
    return std::u16string(reinterpret_cast<const char16_t*>(data), length / 2);
}

std::u32string StringConverter::ConvertUTF32(const char* data, int length) {
    return std::u32string(reinterpret_cast<const char32_t*>(data), length / 4);
}



bool StringConverter::IsSeparator(char32_t ch) {
    return ch == U' ' || ch == U'.' || ch == U',' || ch == U':' || ch == U';' ||
        ch == U'/' || ch == U'\\' || ch == U'\r' || ch == U'\n' || ch == U'\t';
}


std::vector<std::vector<char32_t>> StringConverter::GetUTF32WordsFromUTF8String(const std::string& wyrazenie) {
    if (wyrazenie.empty()) {
        return std::vector<std::vector<char32_t>>();
    }
    std::vector<std::vector<char32_t>> words;
    auto text = UTFConverter::Utf8ToUtf32(wyrazenie);
    UTFConverter::StrToLwrUtf32(text);
    std::vector<char32_t> currentWord;

    for (char32_t ch : text) {
        if (StringConverter::IsSeparator(ch)) {
            if (!currentWord.empty()) {
                words.push_back(currentWord);
                currentWord.clear();
            }
        }
        else {
            currentWord.push_back(ch);
        }
    }

    if (!currentWord.empty()) {
        words.push_back(currentWord);
    }

    // Sortowanie wektora od najdłuższego do najkrótszego słowa
    std::ranges::sort(words, [](const std::vector<char32_t>& a, const std::vector<char32_t>& b) {
        return a.size() > b.size();
        });


    return words;
}



std::vector<std::vector<char32_t>> StringConverter::GetUTF32WordsFromUTF16String(const std::u16string& wyrazenie) {
  
    if (wyrazenie.empty()) {
        return std::vector<std::vector<char32_t>>();
    }

    std::vector<std::vector<char32_t>> words;
 
    auto text = UTFConverter::Utf16ToUtf32(wyrazenie);
   
    UTFConverter::StrToLwrUtf32(text);

    std::u32string u32str(text.begin(), text.end());

   


    std::vector<char32_t> currentWord;
  
    for (char32_t ch : text) {
        if (StringConverter::IsSeparator(ch)) {
            if (!currentWord.empty()) {
                words.push_back(currentWord);
                currentWord.clear();
            }
        }
        else {
            currentWord.push_back(ch);
        }
    }

    if (!currentWord.empty()) {
        words.push_back(currentWord);
    }

    std::ranges::sort(words, [](const std::vector<char32_t>& a, const std::vector<char32_t>& b) {
        return a.size() > b.size();
        });






    return words;
}

std::vector<std::vector<char32_t>> StringConverter::GetUTF32WordsFromUTF32String(const std::u32string& wyrazenie)
{
    if (wyrazenie.empty()) {
        return std::vector<std::vector<char32_t>>();
    }
    std::vector<char32_t> text;
    text.assign(wyrazenie.begin(), wyrazenie.end());
    std::vector<std::vector<char32_t>> words;

    UTFConverter::StrToLwrUtf32(text);

    std::vector<char32_t> currentWord;

    for (char32_t ch : text) {
        if (StringConverter::IsSeparator(ch)) {
            if (!currentWord.empty()) {
                words.push_back(currentWord);
                currentWord.clear();
            }
        }
        else {
            currentWord.push_back(ch);
        }
    }

    if (!currentWord.empty()) {
        words.push_back(currentWord);
    }

    // Sortowanie wektora od najdłuższego do najkrótszego słowa
    std::ranges::sort(words, [](const std::vector<char32_t>& a, const std::vector<char32_t>& b) {
        return a.size() > b.size();
        });


    return words;
}

