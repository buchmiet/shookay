#include "pch.h"
#include "expressionTreeBuilder.h"
#include <queue>
#include <stack>
#include "postfixItem.h"
#include "stringConverter.h"
#include <map>

namespace ExpressionTreeBuilder {

     std::map<WordOperations, int> OperatorPrecedence = {
        { WordOperations::OR, 1 },
        { WordOperations::AND, 2 },
        { WordOperations::NOT, 3 },
        { WordOperations::OpenParenthesis, -1 }, 
        { WordOperations::CloseParenthesis, -1 } 
    };

     std::shared_ptr<ExpressionNode> BuildTree(const std::vector<WordStruct>& wordStructs) {
        auto postfixExpression = ConvertToPostfix(wordStructs);
        std::stack<std::shared_ptr<ExpressionNode>> stack;
        for (const auto& item : postfixExpression) {
            if (item.isOperator()) {
                auto operatorNode = std::make_shared<ExpressionNode>(item.getOperation());
                if (item.getOperation() == WordOperations::NOT) {
                    if (stack.size() < 1) {
                        break;
                    }
                    operatorNode->Left = stack.top();
                    stack.pop();
                }
                else {
                    if (stack.size() < 2) {
                        break;
                    }
                    operatorNode->Right = stack.top();
                    stack.pop();
                    operatorNode->Left = stack.top();
                    stack.pop();
                }
                stack.push(operatorNode);
            }
            else {
                stack.push(std::make_shared<ExpressionNode>(item.getWord()));
            }
        }
        if (stack.empty()) {
            return nullptr;
        }
        auto root = stack.top(); 
        stack.pop();
        return root;
    }

    static std::vector<PostfixItem> ConvertToPostfix(const std::vector<WordStruct>& wordStructs) {
        std::queue<PostfixItem> outputQueue;
        std::stack<WordStruct> operatorStack;
        for (const auto& wordStruct : wordStructs) {
            if (wordStruct.Operation == WordOperations::None) {
                PostfixItem item(wordStruct.Word);
                outputQueue.push(item);
            }
            else if (wordStruct.Operation == WordOperations::OpenParenthesis) {
                operatorStack.push(wordStruct);
            }
            else if (wordStruct.Operation == WordOperations::CloseParenthesis) {
                while (!operatorStack.empty() && operatorStack.top().Operation != WordOperations::OpenParenthesis) {
                    auto const& op = operatorStack.top();
                    operatorStack.pop();
                    PostfixItem item(op.Operation);
                    outputQueue.push(item);
                }
                if (!operatorStack.empty() && operatorStack.top().Operation == WordOperations::OpenParenthesis) {
                    operatorStack.pop();
                }
            }
            else {
                while (!operatorStack.empty() && HasHigherPrecedence(operatorStack.top(), wordStruct)) {
                    auto const& op = operatorStack.top();
                    operatorStack.pop();
                    PostfixItem item(op.Operation);
                    outputQueue.push(item);
                }
                operatorStack.push(wordStruct);
            }
        }

        while (!operatorStack.empty()) {
            auto const& op = operatorStack.top();
            operatorStack.pop();
            if (op.Operation != WordOperations::OpenParenthesis) {
                PostfixItem item(op.Operation);
                outputQueue.push(item);
            }
        }

        std::vector<PostfixItem> postfixList;
        while (!outputQueue.empty()) {
            postfixList.push_back(outputQueue.front());
            outputQueue.pop();
        }

        return postfixList;
    }

    static bool HasHigherPrecedence(const WordStruct& op1, const WordStruct& op2) {
        if (op1.Operation == WordOperations::OpenParenthesis) {
            return false;
        }
        return OperatorPrecedence[op1.Operation] >= OperatorPrecedence[op2.Operation];
    }


}
