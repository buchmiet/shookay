#pragma once
#include <codecvt>
#include <locale>
#include <vector>
#include <string>
#include <algorithm>
#include <string>
#include <map>

namespace StringConverter {
     std::vector<std::vector<char32_t>> GetUTF32WordsFromUTF8String(const std::u8string& wyrazenie);
     std::vector<std::vector<char32_t>> GetUTF32WordsFromUTF16String(const std::u16string& wyrazenie);
     std::vector<std::vector<char32_t>> GetUTF32WordsFromUTF32String(const std::u32string& wyrazenie);   
     std::u8string ConvertUTF8(const char* data, int length);
     std::u16string ConvertUTF16(const char* data, int length);
     std::u32string ConvertUTF32(const char* data, int length);   
     bool IsSeparator(char32_t ch);
     std::vector<std::vector<char32_t>> GetWordsFromString(const std::vector<char32_t> wyrazenie);
    struct VectorHash {
        size_t operator()(const std::vector<char32_t>& v) const {
            std::hash<char32_t> hasher;
            size_t seed = 0;
            for (char32_t i : v) {
                seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };

    template <typename String, typename StringConverter>
    std::map<int, String> ReadEntries(const char* data,  StringConverter converter) {
        std::map<int, String> mapEntries;
        const char* current = data;

        int numEntries;
        memcpy(&numEntries, current, sizeof(int));
        current += sizeof(int);

        for (int i = 0; i < numEntries; ++i) {
            int key;
            memcpy(&key, current, sizeof(int));
            current += sizeof(int);

            int strLength;
            memcpy(&strLength, current, sizeof(int));
            current += sizeof(int);

            mapEntries[key] = converter(current, strLength);
            current += strLength;
        }

        return mapEntries;
    }

};
