#pragma once
#include <codecvt>
#include <locale>
#include <vector>
#include <string>
#include <algorithm>

class StringConverter {
public:

    static std::vector<std::vector<char32_t>> GetUTF32WordsFromUTF8String(const std::string& wyrazenie);
    static std::vector<std::vector<char32_t>> GetUTF32WordsFromUTF16String(const std::u16string& wyrazenie);
    static std::vector<std::vector<char32_t>> GetUTF32WordsFromUTF32String(const std::u32string& wyrazenie);
   
    static std::string ConvertUTF8(const char* data, int length);

    static std::u16string ConvertUTF16(const char* data, int length);

    static std::u32string ConvertUTF32(const char* data, int length);

private:
    static bool IsSeparator(char32_t ch);
};
