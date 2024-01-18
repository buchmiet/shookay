#ifndef EXPRESSIONTOKENIZER_H
#define EXPRESSIONTOKENIZER_H
#include "expressionNode.h"
#include "postfixItem.h"
#include "wordOperations.h"
#include "wordStruct.h"
#include <map>
#include <vector>

namespace ExpressionTokenizer {
     bool IsSeparator(char32_t c);
     std::vector<WordStruct> TokenizeExpression(std::vector<char32_t> expression);
     std::vector<WordStruct> CorrectTokens(std::vector<WordStruct>& tokens);
     void CorrectOperationSequencesAndAddDefaultAND(std::vector<WordStruct>& tokens);
     bool IsInvalidTrailingOperation(WordOperations operation);
     void CorrectOperationSequence(std::vector<WordStruct>& tokens, int& i);
     void InsertDefaultAND(std::vector<WordStruct>& tokens, int i);
     bool AreParenthesesValid(const std::vector<WordStruct>& tokens);
     void RemoveAllParentheses(std::vector<WordStruct>& tokens);
     bool IsOperation(WordOperations operation);
     bool IsConnector(WordOperations operation);
     bool IsInvalidLeadingOperation(WordOperations operation);
     bool IsInvalidTrailingOperation(WordOperations operation);
     void RemoveLeadingAndTrailingOperations(std::vector<WordStruct>& tokens);
};
#endif 