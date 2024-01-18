#pragma once
#include <string>
#include <codecvt>
#include "wordOperations.h"
#include <vector>



class ExpressionNode
{
public:
    WordOperations Operation;
    std::vector<char32_t> Value;
    std::shared_ptr<ExpressionNode> Left;
    std::shared_ptr<ExpressionNode> Right;


    explicit ExpressionNode(WordOperations operation) :Operation(operation) {}
     

    explicit ExpressionNode(std::vector<char32_t> const& value) :Value(value)
    {
        Operation = None;
    }
};