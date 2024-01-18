#ifndef EXPRESSIONTREEBUILDER_H
#define EXPRESSIONTREEBUILDER_H
#include "expressionNode.h"
#include "postfixItem.h"
#include "wordOperations.h"
#include "wordStruct.h"
#include <map>
#include <vector>

namespace ExpressionTreeBuilder{
    std::shared_ptr<ExpressionNode> BuildTree(const std::vector<WordStruct>& wordStructs);
    static bool HasHigherPrecedence(const WordStruct& op1, const WordStruct& op2);
    static std::vector<PostfixItem> ConvertToPostfix(const std::vector<WordStruct>& wordStructs);
};
#endif 