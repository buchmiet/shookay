#pragma once
#include "wordOperations.h"
#include <string>
#include <vector>

struct WordStruct
{
    std::vector<char32_t> Word;
    WordOperations Operation;
    WordStruct(std::vector<char32_t> const& word, WordOperations operation)
        : Word(word), Operation(operation) {}
};
