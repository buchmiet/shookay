#include "pch.h"
#include "wordStruct.h"
#include "expressionTreeBuilder.h"

WordStruct::WordStruct(const std::string& word, WordOperations operation)
    : word(word), operation(operation) {}

const std::string& WordStruct::getWord() const
{
    return word;
}

void WordStruct::setWord(const std::string& newWord)
{
    word = newWord;
}

WordOperations WordStruct::getOperation() const
{
    return operation;
}

void WordStruct::setOperation(WordOperations newOperation)
{
    operation = newOperation;
}


