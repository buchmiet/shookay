#include "pch.h"
#include "stdio.h"
#include <iostream>
#include <vector>
#include <cstdint>
#include <codecvt>
#include <locale>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <stdint.h>
#include <cwctype>
#include "DwordDescription.h"
#include "shookayEngine.h"
#include "StringConverter.h"


shookayEngine::shookayEngine() {

}

void shookayEngine::DeliverEntriesUTF8(const std::map<int, std::string>& entries) {
    std::map<int, std::vector<std::vector<char32_t>>> utf32entries;
    for (const auto& pair : entries) {
        utf32entries[pair.first] = StringConverter::GetUTF32WordsFromUTF8String(pair.second);
    }
    DeliverEntries(utf32entries);
    utf32entries.clear();
}

void shookayEngine::DeliverEntriesUTF16(const std::map<int, std::u16string>& entries) {
    std::map<int, std::vector<std::vector<char32_t>>> utf32entries;
    for (const auto& pair : entries) {
        utf32entries[pair.first] = StringConverter::GetUTF32WordsFromUTF16String(pair.second);
    }
    DeliverEntries(utf32entries);
    utf32entries.clear();
}

void shookayEngine::DeliverEntriesUTF32(const std::map<int, std::u32string>& entries) {
    std::map<int, std::vector<std::vector<char32_t>>> utf32entries;
    for (const auto& pair : entries) {
        utf32entries[pair.first] = StringConverter::GetUTF32WordsFromUTF32String(pair.second);
    }
    DeliverEntries(utf32entries);
    utf32entries.clear();
}

void shookayEngine::DeliverEntries(const std::map<int, std::vector<std::vector<char32_t>>>& utf32entries) {


    std::vector<int> initTable;
    std::vector<DwordDescription> initDescriptions;
    std::vector<int> initLocations;
    recordOffsets.resize(utf32entries.size());
    recordIds.resize(utf32entries.size());

    int currentPointer = 0;
    int j = 0;

    for (const auto& entry : utf32entries) {
        recordIds[j] = entry.first;
        recordOffsets[j] = currentPointer;
        for (const auto& item : entry.second) {

            auto& innerEntries = item;
            for (size_t i = 0; i < innerEntries.size(); ++i) {
                DwordDescription dd;

                if (i == 0) {
                    dd.isBeginningOfTheWord = 1;
                }
                dd.charIndex = static_cast<uint8_t>(i);
                dd.wordLength = static_cast<uint8_t>(innerEntries.size());
                dd.charIndexFromTheEnd = static_cast<uint8_t>(dd.wordLength - dd.charIndex);
                initTable.push_back(innerEntries[i]);
                initDescriptions.push_back(dd);
                initLocations.push_back(entry.first);
                currentPointer++;
            }
        }
        j++;
    }
    contentArray = std::move(initTable);
    descriptionArray = std::move(initDescriptions);
    locationArray = std::move(initLocations);
}


extern "C" void FindExactWordsUntilTheContentIsTooSmallOrEndOfRecordAsm(
    int totalRecordCount,
    int* recordOffsets,
    int* results,
    int* locationArray,
    int* recordIds,
    int* contentArray,
    int contentArraySize,
    DwordDescription * descriptionArray,
    const char32_t* searchExpressionItem,
    uint8_t searchExpressionLength
);

extern "C" void FindWordsWithinUntilTheContentIsTooSmallOrEndOfRecordAsm(
    int totalRecordCount,
    int* recordOffsets,
    int* results,
    int* locationArray,
    int* recordIds,
    int* contentArray,
    int contentArraySize,
    DwordDescription * descriptionArray,
    const char32_t* searchExpressionItem,
    uint8_t searchExpressionLength
);



bool shookayEngine::CompareWordsUntilTheContentIsTooSmallOrEndOfRecord(const std::vector<char32_t>& SearchExpression, int pointerToEndOfTheRecord, int& IndexToCharInContentArray)
{
    uint8_t searchExpressionLength = static_cast<uint8_t>(SearchExpression.size());

    if (descriptionArray[IndexToCharInContentArray].wordLength < searchExpressionLength) {
        IndexToCharInContentArray += descriptionArray[IndexToCharInContentArray].wordLength;
        return false;
    }

    while (IndexToCharInContentArray < pointerToEndOfTheRecord && descriptionArray[IndexToCharInContentArray].wordLength >= searchExpressionLength) {
        int endOfWord = IndexToCharInContentArray + descriptionArray[IndexToCharInContentArray].charIndexFromTheEnd;

        while (IndexToCharInContentArray + searchExpressionLength <= endOfWord)
        {
            bool match = true;

            for (int x = 0; x < searchExpressionLength; x++) {
                if (contentArray[IndexToCharInContentArray + x] != SearchExpression[x]) {
                    match = false;
                    IndexToCharInContentArray++;
                    break;
                }
            }

            if (match) {
                IndexToCharInContentArray = pointerToEndOfTheRecord;
                return true;
            }
        }

        IndexToCharInContentArray += descriptionArray[IndexToCharInContentArray].charIndexFromTheEnd;
    }

    return false;
};


std::vector<int> shookayEngine::FindWithinUTF8(const char* wyrazenie) {

    return FindWithin(StringConverter::GetUTF32WordsFromUTF8String(wyrazenie));
}



std::vector<int> shookayEngine::FindWithinUTF16(const char16_t* wyrazenie){
   
    return FindWithin(StringConverter::GetUTF32WordsFromUTF16String(wyrazenie));     
}
std::vector<int> shookayEngine::FindWithinUTF32(const char32_t* wyrazenie) {

    return FindWithin(StringConverter::GetUTF32WordsFromUTF32String(wyrazenie));
}

std::vector<int> shookayEngine::FindExactUTF8(const char* wyrazenie) {
    return FindExact(StringConverter::GetUTF32WordsFromUTF8String(wyrazenie));
}
std::vector<int> shookayEngine::FindExactUTF16(const char16_t* wyrazenie) {
   
    return FindExact(StringConverter::GetUTF32WordsFromUTF16String(wyrazenie));
}
std::vector<int> shookayEngine::FindExactUTF32(const char32_t* wyrazenie) {
    return FindExact(StringConverter::GetUTF32WordsFromUTF32String(wyrazenie));
}

std::vector<int> shookayEngine::FindExact(const std::vector<std::vector<char32_t>> expressions) {

    std::vector<int> returnVector;
    int totalRecordCount = recordOffsets.size();
    results = std::vector<int>(totalRecordCount, 1);
    int currentRecordIndex; // Index of the current record
    int indexToCharInContentArray; // Index to character in the content array
    bool found = false; // Flag indicating whether a matching record was found

    auto SkipToFirstRecordThatIsOkToLookFor = [&]()
        {
            while (currentRecordIndex < totalRecordCount && results[currentRecordIndex] == 0)
            {
                currentRecordIndex++;
                if (currentRecordIndex < totalRecordCount)
                {
                    indexToCharInContentArray = recordOffsets[currentRecordIndex];
                }
            }
        };

    auto CompareWordsUntilTheContentIsTooSmallOrEndOfRecord = [&](const std::vector<char32_t>& SearchExpression, int pointerToEndOfTheRecord) -> bool
        {
            uint8_t searchExpressionLength = static_cast<uint8_t>(SearchExpression.size());
            while (indexToCharInContentArray < pointerToEndOfTheRecord && descriptionArray[indexToCharInContentArray].wordLength == searchExpressionLength)
            {
                for (int x = 0; x < searchExpressionLength; x++)
                {
                    if (contentArray[indexToCharInContentArray + x] != SearchExpression[x])
                    {
                        indexToCharInContentArray += searchExpressionLength;
                        break;
                    }
                }
                indexToCharInContentArray = pointerToEndOfTheRecord;
                return true;
            }
            return false;
        };

    for (auto& expressionsItem : expressions)
    {
        if (expressionsItem.size() > 16)
        {
            indexToCharInContentArray = 0;
            currentRecordIndex = 0;
            while (currentRecordIndex < totalRecordCount)
            {
                SkipToFirstRecordThatIsOkToLookFor();
                if (currentRecordIndex == totalRecordCount) {
                    break;
                }
                int endOfCurrentRecordPointer = 0;
                if (currentRecordIndex == totalRecordCount - 1) {
                    endOfCurrentRecordPointer = contentArray.size();
                }
                else {
                    endOfCurrentRecordPointer = recordOffsets[currentRecordIndex + 1];
                }
                found = false;
                while (indexToCharInContentArray < endOfCurrentRecordPointer && !found)
                {
                    if (descriptionArray[indexToCharInContentArray].wordLength < expressionsItem.size())
                    {
                        indexToCharInContentArray = endOfCurrentRecordPointer;
                    }
                    else
                    {
                        while (descriptionArray[indexToCharInContentArray].wordLength > expressionsItem.size())
                        {
                            indexToCharInContentArray += descriptionArray[indexToCharInContentArray].wordLength;
                        }
                        found = CompareWordsUntilTheContentIsTooSmallOrEndOfRecord(expressionsItem, endOfCurrentRecordPointer);
                    }
                }
                if (!found) {
                    results[currentRecordIndex] = 0;
                }
                currentRecordIndex++;
            }
        }
        else
        {
            FindExactWordsUntilTheContentIsTooSmallOrEndOfRecordAsm(
                totalRecordCount,
                recordOffsets.data(),
                results.data(),
                locationArray.data(),
                recordIds.data(),
                contentArray.data(),
                contentArray.size(),
                descriptionArray.data(),
                expressionsItem.data(),
                expressionsItem.size()
            );
        }
    }

    for (size_t x = 0; x < results.size(); x++) {
        if (results[x] == 1) {
            returnVector.push_back(recordIds[x]);
        }
    }
    return returnVector;
}




std::vector<int> shookayEngine::FindWithin(const std::vector<std::vector<char32_t>> expressions)
{

   
    std::vector<int> returnVector;
    int totalRecordCount = recordOffsets.size();
    results = std::vector<int>(totalRecordCount, 1);
    int currentRecordIndex; // Index of the current record
    int indexToCharInContentArray; // Index to character in the content array
    bool found = false; // Flag indicating whether a matching record was found
    auto SkipToFirstRecordThatIsOkToLookFor = [&]()
        {
            while (currentRecordIndex < totalRecordCount && results[currentRecordIndex] == 0)
            {
                currentRecordIndex++;
                if (currentRecordIndex < totalRecordCount)
                {
                    indexToCharInContentArray = recordOffsets[currentRecordIndex];
                }
            }
        };
    for (auto& expressionsItem : expressions)
    {

        if (expressionsItem.size() > 16)
        {
            indexToCharInContentArray = 0;
            currentRecordIndex = 0;
            while (currentRecordIndex < totalRecordCount)
            {
                SkipToFirstRecordThatIsOkToLookFor();
                if (currentRecordIndex == totalRecordCount) {
                    break;
                }
                int endOfCurrentRecordPointer = 0;
                if (currentRecordIndex == totalRecordCount - 1) {
                    endOfCurrentRecordPointer = contentArray.size();
                }
                else {
                    endOfCurrentRecordPointer = recordOffsets[currentRecordIndex + 1];
                }
                found = false;
                while (indexToCharInContentArray < endOfCurrentRecordPointer && !found)
                {
                    found = CompareWordsUntilTheContentIsTooSmallOrEndOfRecord(expressionsItem, endOfCurrentRecordPointer, indexToCharInContentArray);
                }
                if (!found) {
                    results[currentRecordIndex] = 0;
                }
                currentRecordIndex++;
            }
        }
        else
        {
          
            FindWordsWithinUntilTheContentIsTooSmallOrEndOfRecordAsm(
                totalRecordCount,
                recordOffsets.data(),
                results.data(),
                locationArray.data(),
                recordIds.data(),
                contentArray.data(),
                contentArray.size(),
                descriptionArray.data(),
                expressionsItem.data(),
                expressionsItem.size()
            );
          
        }
    }

    for (size_t x = 0; x < results.size(); x++) {
        if (results[x] == 1) {
            returnVector.push_back(recordIds[x]);
        }
    }
    return returnVector;
}
