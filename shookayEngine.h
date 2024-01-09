#pragma once
#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include "DwordDescription.h"
#include <fstream>
#include "common.h"

class  shookayEngine {
public:
    shookayEngine();
    void DeliverEntries(const std::map<int, std::vector<std::vector<char32_t>>>& utf32entries);
    void DeliverEntriesWithCallback(const std::map<int, std::vector<std::vector<char32_t>>>& utf32entries, ProgressCallback progressCallback);
    void DeliverEntriesUTF8(const std::map<int, std::string>& entries);
    void DeliverEntriesUTF8WithCallback(const std::map<int, std::string>& entries, ProgressCallback progressCallback);
    void DeliverEntriesUTF16(const std::map<int, std::u16string>& entries);
    void DeliverEntriesUTF16WithCallback(const std::map<int, std::u16string>& entries, ProgressCallback progressCallback);
    void DeliverEntriesUTF32(const std::map<int, std::u32string>& entries);
    void DeliverEntriesUTF32WithCallback(const std::map<int, std::u32string>& entries, ProgressCallback progressCallback);
    std::vector<int> FindWithinUTF8(const char* wyrazenie); 
    std::vector<int> FindWithinUTF16(const char16_t* wyrazenie);
    std::vector<int> FindWithinUTF32(const char32_t* wyrazenie);
    std::vector<int> FindExactUTF8(const char* wyrazenie);
    std::vector<int> FindExactUTF16(const char16_t* wyrazenie);
    std::vector<int> FindExactUTF32(const char32_t* wyrazenie);


    template <typename String, typename StringConverter>
    static std::map<int, String> ReadEntries(const char* data, int length, StringConverter converter) {
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

   


private:

    bool CompareWordsUntilTheContentIsTooSmallOrEndOfRecord(const std::vector<char32_t>& WyszukiwaneWyrazenie, int pointerToEndOfTheRecord, int& IndexToCharInContentArray);
    std::vector<int> FindWithin(const std::vector<std::vector<char32_t>> wyrazenia);
    std::vector<int> FindExact(const std::vector<std::vector<char32_t>> wyrazenia);
    std::vector<int> locationArray;
    std::vector<int> recordOffsets;
    std::vector<int> results;
    std::vector<int> recordIds;
    std::vector<int> contentArray;
    std::vector<DwordDescription> descriptionArray;
    std::string architectureFlag;
};