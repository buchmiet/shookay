#include "pch.h"
#include <vector>
#include <string>
#include <map>
#include <stdint.h>
#include "shookayEngine.h"
#include "stringConverter.h"
#include "quickSorter.h"
#include "myIntHashSet.h"
#include "wordMatchMethod.h"
#include <ranges>
#include "expressionTokenizer.h"
#include "expressionTreeBuilder.h"
#include "utfConv.h"
#include <algorithm>
#include <iostream>



shookayEngine::shookayEngine() = default;

void shookayEngine::PrepareEntriesUTF8(const std::map<int, std::u8string>& entries) {
    std::map<int, std::vector<std::vector<char32_t>>> utf32entries;
    for (const auto& pair : entries) {
        utf32entries[pair.first] = StringConverter::GetUTF32WordsFromUTF8String(pair.second);
    }
    PrepareEntries(utf32entries);
    utf32entries.clear();
}


void shookayEngine::PrepareEntriesUTF16(const std::map<int, std::u16string>& entries) {

    std::map<int, std::vector<std::vector<char32_t>>> utf32entries;
    for (const auto& pair : entries) {

      
        utf32entries[pair.first] = StringConverter::GetUTF32WordsFromUTF16String(pair.second);     
    }   
    
    PrepareEntries(utf32entries);
    utf32entries.clear();

}


void shookayEngine::PrepareEntriesUTF32(const std::map<int, std::u32string>& entries) {
    std::map<int, std::vector<std::vector<char32_t>>> utf32entries;
    for (const auto& pair : entries) {
        utf32entries[pair.first] = StringConverter::GetUTF32WordsFromUTF32String(pair.second);
    }
    PrepareEntries(utf32entries);
    utf32entries.clear();
}

void shookayEngine::PrepareEntries(const std::map<int, std::vector<std::vector<char32_t>>>& utf32entries) {
    
    int i = 0;
    int j = 0;

    int totalLengthOfWordsArray = 0;
    int totalNumberOfIndices = 0;
    recordIds.resize(utf32entries.size());
    
    for (const auto& [key, value] : utf32entries)
    {
        recordIds[j] = key;
        recordIdsDict[key] = j;        
        for (const auto& item : value)
        {
            auto it = invertedIndex.find(item);
            if (it == invertedIndex.end()) {
                invertedIndex[item] = std::vector<int>{ key };             
                wordDescriptions.push_back(WordDescription{ &(*invertedIndex.find(item)), static_cast<int>(item.size()) });
                totalNumberOfIndices++;
                totalLengthOfWordsArray += item.size();
                i++;
            }
            else {
           
                it->second.push_back(key);
                totalNumberOfIndices++;
            }          
        }
        j++;
    }
    
    QuickSorter::Sort(wordDescriptions);
    wordsArray.resize(totalLengthOfWordsArray);
    indicesArray.resize(totalNumberOfIndices);
    numbersOfIndices.resize(wordDescriptions.size());
    i = 0;
    size_t totalOffset = 0;
    size_t localLength;
    wordLengths.resize(invertedIndex.size());
    wordEnds.resize(invertedIndex.size());
    indicesArrayOffsets.resize(invertedIndex.size());
    int pointer2IndicesArray = 0;

    for (const auto& item : wordDescriptions) {
        const auto& pair = *(item.pairPtr);
      
        localLength = pair.first.size();
      
        std::ranges::copy(pair.first.begin(), pair.first.begin() + localLength, wordsArray.begin() + totalOffset);
      
        numbersOfIndices[i] = pair.second.size();
        indicesArrayOffsets[i] = pointer2IndicesArray;
      
        for (const int item2 : pair.second) {
            indicesArray[pointer2IndicesArray] = recordIdsDict[item2];
            pointer2IndicesArray++;
        }

        totalOffset += localLength;
        wordLengths[i] = localLength;
        wordEnds[i] = totalOffset;
        i++;
    } 
}


void shookayEngine::PrepareEntriesUTF8WithCallback(const std::map<int, std::u8string>& entries, ProgressCallback progressCallback) {
    std::map<int, std::vector<std::vector<char32_t>>> utf32entries;
    for (const auto& pair : entries) {
        utf32entries[pair.first] = StringConverter::GetUTF32WordsFromUTF8String(pair.second);
    }
    PrepareEntriesWithCallback(utf32entries, progressCallback);
    utf32entries.clear();
}

void shookayEngine::PrepareEntriesUTF16WithCallback(const std::map<int, std::u16string>& entries, ProgressCallback progressCallback) {
    std::map<int, std::vector<std::vector<char32_t>>> utf32entries;
    for (const auto& pair : entries) {
        utf32entries[pair.first] = StringConverter::GetUTF32WordsFromUTF16String(pair.second);
    }      
    PrepareEntriesWithCallback(utf32entries, progressCallback);
    utf32entries.clear();
}


void shookayEngine::PrepareEntriesUTF32WithCallback(const std::map<int, std::u32string>& entries, ProgressCallback progressCallback) {
    std::map<int, std::vector<std::vector<char32_t>>> utf32entries;
    for (const auto& pair : entries) {
        utf32entries[pair.first] = StringConverter::GetUTF32WordsFromUTF32String(pair.second);
    }
    PrepareEntriesWithCallback(utf32entries, progressCallback);
}


void shookayEngine::AddEntry(int id, std::vector<std::vector<char32_t>>  wyrazenie) {
    int i = 0;   
    recordIds.push_back(id);
    recordIdsDict[id] = recordIds.size() - 1;
    int newords = 0;
    int newindices = 0;
    int totalLengthOfWordsArray = 0;

        for (const auto& item : wyrazenie)
        {
            auto it = invertedIndex.find(item);
            if (it == invertedIndex.end()) {
                invertedIndex[item] = std::vector<int>{ id };
                wordDescriptions.push_back(WordDescription{ &(*invertedIndex.find(item)), static_cast<int>(item.size()) });
                newords++;
                newindices++;
                totalLengthOfWordsArray += item.size();
                i++;
            }
            else {

                it->second.push_back(id);
                newindices++;
            }
        }

       

    

    QuickSorter::Sort(wordDescriptions);

    int x = wordsArray.size() + totalLengthOfWordsArray;
    wordsArray.resize(x);
  

    indicesArray.resize(indicesArray.size()+ newindices);
    numbersOfIndices.resize(wordDescriptions.size());
    i = 0;
    size_t totalOffset = 0;
    size_t localLength;

  
    wordLengths.resize(invertedIndex.size());

  
    wordEnds.resize(invertedIndex.size());

  
    indicesArrayOffsets.resize(invertedIndex.size());
    int pointer2IndicesArray = 0;

    
    
    
    

    for (const auto& item : wordDescriptions) {
        const auto& pair = *(item.pairPtr);
        localLength = pair.first.size();
        std::ranges::copy(pair.first.begin(), pair.first.begin() + localLength, wordsArray.begin() + totalOffset);
        numbersOfIndices[i] = pair.second.size();
        indicesArrayOffsets[i] = pointer2IndicesArray;
        for (const int item2 : pair.second) {
            indicesArray[pointer2IndicesArray] = recordIdsDict[item2];
            pointer2IndicesArray++;
        }
        totalOffset += localLength;
        wordLengths[i] = localLength;
        wordEnds[i] = totalOffset;
     
        i++;
    }



}


void shookayEngine::PrepareEntriesWithCallback(const std::map<int, std::vector<std::vector<char32_t>>>& utf32entries, ProgressCallback progressCallback) {

    int i = 0;
    int j = 0;

    int totalLengthOfWordsArray = 0;
    int totalNumberOfIndices = 0;
    recordIds.resize(utf32entries.size());
    size_t totalSize = utf32entries.size();
    for (const auto& [key, value] : utf32entries)
    {
        recordIds[j] = key;
        recordIdsDict[key] = j;
        for (const auto& item : value)
        {
            auto it = invertedIndex.find(item);
            if (it == invertedIndex.end()) {
                invertedIndex[item] = std::vector<int>{ key };
                wordDescriptions.push_back(WordDescription{ &(*invertedIndex.find(item)), static_cast<int>(item.size()) });
                totalNumberOfIndices++;
                totalLengthOfWordsArray += item.size();
                i++;
            }
            else {

                it->second.push_back(key);
                totalNumberOfIndices++;
            }
        }

        float progress = static_cast<float>(j) / totalSize * 50.0f; 
        if (progressCallback != nullptr) {
            progressCallback(progress);
        }
        j++;
    }

    QuickSorter::Sort(wordDescriptions);
    wordsArray.resize(totalLengthOfWordsArray);
    indicesArray.resize(totalNumberOfIndices);
    numbersOfIndices.resize(wordDescriptions.size());
    i = 0;
    size_t totalOffset = 0;
    size_t localLength;
    wordLengths.resize(invertedIndex.size());
    wordEnds.resize(invertedIndex.size());
    indicesArrayOffsets.resize(invertedIndex.size());
    int pointer2IndicesArray = 0;

    totalSize = wordDescriptions.size();
    for (const auto& item : wordDescriptions) {
        const auto& pair = *(item.pairPtr);
        localLength = pair.first.size();
        std::ranges::copy(pair.first.begin(), pair.first.begin() + localLength, wordsArray.begin() + totalOffset);
        numbersOfIndices[i] = pair.second.size();
        indicesArrayOffsets[i] = pointer2IndicesArray;
        for (const int item2 : pair.second) {
            indicesArray[pointer2IndicesArray] = recordIdsDict[item2];
            pointer2IndicesArray++;
        }
        totalOffset += localLength;
        wordLengths[i] = localLength;
        wordEnds[i] = totalOffset;
        float progress = 50.0f + (static_cast<float>(i) / totalSize * 50.0f); 
        if (progressCallback != nullptr) {
            progressCallback(progress);
        }
        i++;
    }
}

std::vector<int> shookayEngine::Find(const std::vector<char32_t>& wyrazenia, WordMatchMethod method){  
    std::vector<char32_t> wyrazeniaVec(wyrazenia.begin(), wyrazenia.end());
    UTFConverter::StrToLwrUtf32(wyrazeniaVec);
    MyIntHashSet IndicesOffAllRecordsMatchingSearchTerm(recordIds);
    auto dzialania = ExpressionTokenizer:: TokenizeExpression(wyrazeniaVec);
    auto goodyts = ExpressionTokenizer::CorrectTokens(dzialania);
    auto root = ExpressionTreeBuilder::BuildTree(goodyts);    
    auto zwrotka = ProcessNode(root, IndicesOffAllRecordsMatchingSearchTerm, method);
    std::vector<int> retka;
    for (int k = 0; k < zwrotka->Length(); k++)
    {
        if (zwrotka->Ints()[k] ==1)
        {
            retka.push_back(recordIds[k]);            
        }
    }
    return retka;
}

MyIntHashSet shookayEngine::IsTheWordMatch(const std::vector<char32_t>& word, WordMatchMethod method){    
    size_t length = word.size();
    int currentWordArrayIndex = 0;
    int x = 0;
    if (method == Exact)
    {
        while (wordLengths[x] > length && x < wordLengths.size())
        {
            x++;
        }
    }
    auto zwrotka = MyIntHashSet(recordIds.size());
    while (x < wordLengths.size() && wordLengths[x] >= length)
    {
        int pointer2IndicesArray = indicesArrayOffsets[x];
        int numberOfIndices = numbersOfIndices[x];
        currentWordArrayIndex = wordEnds[x] - wordLengths[x];
        auto wordWhereFirstWordCanBe = wordsArray | std::views::drop(currentWordArrayIndex) | std::views::take(wordLengths[x]);
        CheckIfWordIsAMatchWithinAndReturnIndices(zwrotka, word, wordWhereFirstWordCanBe, pointer2IndicesArray, numberOfIndices, currentWordArrayIndex);
        x++;
    }
    return zwrotka;
}

std::shared_ptr<MyIntHashSet> shookayEngine::ProcessNode(const std::shared_ptr<ExpressionNode>& node, MyIntHashSet& allRecords, WordMatchMethod method) {   
    if (node->Operation == WordOperations::None) {
        const auto& zwro = node->Value;        
        return std::make_shared<MyIntHashSet>(IsTheWordMatch(zwro, method));
    }    
    std::shared_ptr<MyIntHashSet> leftSet = (node->Left != nullptr) ? ProcessNode(node->Left, allRecords, method) : nullptr;
    std::shared_ptr<MyIntHashSet> rightSet = (node->Right != nullptr) ? ProcessNode(node->Right, allRecords, method) : nullptr;    
    if (node->Operation == WordOperations::AND) {
        if (leftSet && rightSet) {
            leftSet->IntersectWith(*rightSet);
        }
        return leftSet;
    }
    else if (node->Operation == WordOperations::OR) {
        if (leftSet && rightSet) {
            leftSet->UnionWith(*rightSet);
        }
        return leftSet;
    }
    else if (node->Operation == WordOperations::NOT) {
        if (leftSet) {
            allRecords.ExceptWith(*leftSet);
        }
        return std::make_shared<MyIntHashSet>(allRecords);
    }
    return nullptr;
}

void shookayEngine::CheckIfWordIsAMatchWithinAndReturnIndices(MyIntHashSet& indices,const std::vector<char32_t>& wordToLookFor, const std::ranges::subrange<std::vector<int>::iterator>& wordWhereFirstWordCanBe, int pointer2IndicesArray, int numberOfIndices, int& internalCurrentWordArrayIndex)
{
    int j;
    size_t wordEnd = internalCurrentWordArrayIndex + wordWhereFirstWordCanBe.size();
    while (internalCurrentWordArrayIndex + wordToLookFor.size() <= wordEnd)
    {
        j = 0;
        while (j < wordToLookFor.size() && wordsArray[internalCurrentWordArrayIndex + j] == wordToLookFor[j])
        {
            j++;
        }
        if (j == wordToLookFor.size())
        {
            for (int k = 0; k < numberOfIndices; k++)
            {
                indices.Add(indicesArray[pointer2IndicesArray + k]);
            }
            break;
        }
        internalCurrentWordArrayIndex++;
    }
}


std::vector<int> shookayEngine::FindUTF8(const char8_t* wyrazenie, WordMatchMethod method) {
    auto wyrazenia = UTFConverter::Utf8ToUtf32(wyrazenie);
    return Find(wyrazenia, method);
}


std::vector<int> shookayEngine::FindUTF16(const char16_t* wyrazenie, WordMatchMethod method){    
    auto wyrazenia = UTFConverter::Utf16ToUtf32(wyrazenie);
    return Find(wyrazenia, method);
}



std::vector<int> shookayEngine::FindUTF32(const char32_t* wyrazenie, WordMatchMethod method){
    std::vector<char32_t> vec;
    while (*wyrazenie != '\0') { 
        vec.push_back(*wyrazenie);
        wyrazenie++; 
    }
    return Find(std::vector<char32_t>(vec.begin(), vec.end()), method);
}

void shookayEngine::AddEntryUTF8(int id, const char8_t* wyrazenie) {
    AddEntry(id, StringConverter::GetUTF32WordsFromUTF8String(wyrazenie));
}


void shookayEngine::AddEntryUTF16(int id, const char16_t* wyrazenie) {
    AddEntry(id, StringConverter::GetUTF32WordsFromUTF16String(wyrazenie));
}

void shookayEngine::AddEntryUTF32(int id, const char32_t* wyrazenie) {
    AddEntry(id, StringConverter::GetUTF32WordsFromUTF32String(wyrazenie));
}
