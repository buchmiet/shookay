#include "pch.h"
#include "StringConverter.h"
#include <cwctype>
#include <chrono>
#include <iostream>
#include "UtfConv.h"
#include <algorithm>
#include <unordered_set>


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
    return GetWordsFromString(UTFConverter::Utf8ToUtf32(wyrazenie));  
}


std::vector<std::vector<char32_t>> StringConverter::GetUTF32WordsFromUTF16String(const std::u16string& wyrazenie) {
  
    if (wyrazenie.empty()) {
        return std::vector<std::vector<char32_t>>();
    }      
    return GetWordsFromString(UTFConverter::Utf16ToUtf32(wyrazenie));   
}

std::vector<std::vector<char32_t>> StringConverter::GetUTF32WordsFromUTF32String(const std::u32string& wyrazenie)
{
    if (wyrazenie.empty()) {
        return std::vector<std::vector<char32_t>>();
    }
    std::vector<char32_t> text;
    text.assign(wyrazenie.begin(), wyrazenie.end());
    return GetWordsFromString(text);   
}


std::vector<std::vector<char32_t>> StringConverter::GetWordsFromString(std::vector<char32_t> wyrazenie) {
    std::vector<std::vector<char32_t>> words;
    std::unordered_set<std::vector<char32_t>,  VectorHash> uniqueWords;

    UTFConverter::StrToLwrUtf32(wyrazenie);
    std::u32string u32str(wyrazenie.begin(), wyrazenie.end());
    std::vector<char32_t> currentWord;
    for (char32_t ch : wyrazenie) {
        if (StringConverter::IsSeparator(ch)) {
            if (!currentWord.empty()) {
                if (!uniqueWords.contains(currentWord)) { 
                    uniqueWords.insert(currentWord); 
                    words.push_back(currentWord); 
                }
                currentWord.clear();
            }
        }
        else {
            currentWord.push_back(ch);
        }
    }

    if (!currentWord.empty() && !uniqueWords.contains(currentWord)) {
        words.push_back(currentWord);
    }
  
    std::ranges::sort(words, [](const std::vector<char32_t>& a, const std::vector<char32_t>& b) {
        return a.size() > b.size();
        });
  
    for (const auto& word : words) {
        for (char32_t ch : word) {
            std::wcout << static_cast<wchar_t>(ch);
        }
        std::cout << std::endl;
    }


    return words;
}