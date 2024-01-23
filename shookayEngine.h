#pragma once
#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include <fstream>
#include "common.h"
#include "wordDescription.h"
#include <ranges>
#include "myIntHashSet.h"
#include "common.h"
#include "expressionNode.h"

class  shookayEngine {
public:

	shookayEngine();
	void PrepareEntriesWithCallback(const std::map<int, std::vector<std::vector<char32_t>>>& utf32entries, ProgressCallback progressCallback);
	void PrepareEntries(const std::map<int, std::vector<std::vector<char32_t>>>& utf32entries);
	void PrepareEntriesUTF8WithCallback(const std::map<int, std::u8string>& entries, ProgressCallback progressCallback);
	void PrepareEntriesUTF16WithCallback(const std::map<int, std::u16string>& entries, ProgressCallback progressCallback);
	void PrepareEntriesUTF32WithCallback(const std::map<int, std::u32string>& entries, ProgressCallback progressCallback);
	void PrepareEntriesUTF8(const std::map<int, std::u8string>& entries);
	void PrepareEntriesUTF16(const std::map<int, std::u16string>& entries);
	void PrepareEntriesUTF32(const std::map<int, std::u32string>& entries);
	std::vector<int> FindUTF8(const char8_t* wyrazenie, WordMatchMethod method);
	std::vector<int> FindUTF16(const char16_t* wyrazenie, WordMatchMethod method);
    std::vector<int> FindUTF32(const char32_t* wyrazenie, WordMatchMethod method);
	void AddEntryUTF8(int id, const char8_t* wyrazenie);
	void AddEntryUTF16(int id,const char16_t* wyrazenie);
	void AddEntryUTF32(int id, const char32_t* wyrazenie);
	void AddEntry(int id, std::vector<std::vector<char32_t>> wyrazenie);

private:
	
	std::vector<int> Find(const std::vector<char32_t>& wyrazenia, WordMatchMethod method);
	std::shared_ptr<MyIntHashSet> ProcessNode(const std::shared_ptr<ExpressionNode>& node, MyIntHashSet& allRecords, WordMatchMethod method);
	MyIntHashSet IsTheWordMatch(const std::vector<char32_t>& word, WordMatchMethod method);
	void CheckIfWordIsAMatchWithinAndReturnIndices(MyIntHashSet& indices, const std::vector<char32_t>& wordToLookFor, const std::ranges::subrange<std::vector<int>::iterator>& wordWhereFirstWordCanBe, int pointer2IndicesArray, int numberOfIndices, int& internalCurrentWordArrayIndex);
	std::vector<int> recordIds;
	std::vector<int> indicesArray;
	std::vector<int> indicesArrayOffsets;
	std::vector<int> wordEnds;
	std::vector<int> wordLengths;
	std::vector<int> wordsArray;
	std::map<std::vector<char32_t>, std::vector<int>> invertedIndex;
	std::map<int, int> recordIdsDict;
	std::vector<int> numbersOfIndices;
	std::vector<WordDescription> wordDescriptions;
};