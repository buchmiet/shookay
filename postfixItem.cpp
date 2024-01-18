#include "pch.h"
#include "postfixItem.h"
#include "wordOperations.h"
#include <vector>


PostfixItem::PostfixItem(const std::vector<char32_t>& inWord)   : word(inWord)
{    
    operation = WordOperations::None;
}

PostfixItem::PostfixItem(const WordOperations & op) : operation(op) {
}


std::vector<char32_t> PostfixItem::getWord() const {
    return word;
}

void PostfixItem::setWord(const std::vector<char32_t>& inWord) {
    this->word = inWord;
}

WordOperations PostfixItem::getOperation() const {
    return operation;
}

void PostfixItem::setOperation(WordOperations op) {
    operation = op;
}

bool PostfixItem::isOperator() const {
    return operation != WordOperations::None;
}
