#ifndef POSTFIXITEM_H
#define POSTFIXITEM_H

#include <string>
#include "wordOperations.h"
#include <vector>

class PostfixItem {
public:
    explicit PostfixItem(const std::vector<char32_t>& inWord); 
    explicit PostfixItem(const WordOperations& op);
    std::vector<char32_t> getWord() const;
    void setWord(const std::vector<char32_t>& word);
    WordOperations getOperation() const;
    void setOperation(WordOperations op);
    bool isOperator() const;

private:
    std::vector<char32_t> word;
    WordOperations operation;
};

#endif
