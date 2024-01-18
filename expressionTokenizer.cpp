#include "pch.h"
#include "expressionTokenizer.h"
#include "vector"
#include <ranges>
#include "wordOperations.h"
#include <algorithm>
#include "wordStruct.h"

namespace ExpressionTokenizer
{

    std::map<std::u32string, WordOperations> WordDictionary = {
      {U"or", WordOperations::OR},
      {U"and", WordOperations::AND},
      {U"not", WordOperations::NOT },
      {U"(", WordOperations::OpenParenthesis },
      {U")", WordOperations::CloseParenthesis }
    };
    static bool IsSeparator(char32_t c)
    {
        return c == '|' || c == ' ' || c == '-' || c == '.' || c == '/' || c == '\n' || c == '\r' || c == '\\' || c == ',' || c == '#' || c == '[' || c == ']' || c == '{' || c == '~' || c == '}' || c == ':'
            || c == ';' || c == '$' || c == '£' || c == '€';
    }

     std::vector<WordStruct> TokenizeExpression(std::vector<char32_t> expression)
    {
        std::vector < WordStruct> tokens;      
        std::vector<char32_t> currentWord ;
        
        for (const auto& ch : expression)
        {
            std::u32string chAsString(1, ch);
            auto it = WordDictionary.find(chAsString);
            if (IsSeparator(ch) || it != WordDictionary.end()) 
            {
                auto ope = WordDictionary.find(std::u32string(currentWord.begin(), currentWord.end()));
                if (!currentWord.empty())
                {
                    WordStruct word(currentWord,                        
                        ope != WordDictionary.end()?                        
                        WordDictionary[std::u32string(currentWord.begin(), currentWord.end())]:
                        WordOperations::None
                    );
                    tokens.push_back(word);
                    currentWord.clear();
                }
           
                if (it != WordDictionary.end()) {
                    WordStruct word(currentWord, WordDictionary[chAsString]);
                    tokens.push_back(word);
                }               
            }
            else
            {
                currentWord.push_back(ch);
            }
        }
        if (!currentWord.empty())
        {
            WordStruct word(currentWord, WordOperations::None);
            tokens.push_back(word);
        }       
        return tokens;
    }
 
     std::vector<WordStruct> CorrectTokens(std::vector<WordStruct>& tokens)
    {
        if (tokens.empty())
        {
            return tokens;
        }     
        RemoveLeadingAndTrailingOperations(tokens);        
        CorrectOperationSequencesAndAddDefaultAND(tokens);        
        if (!AreParenthesesValid(tokens))
        {
            RemoveAllParentheses(tokens);
        }
        return tokens;
    }

    static void RemoveLeadingAndTrailingOperations(std::vector<WordStruct>& tokens)
    {       
        while (!tokens.empty() && IsInvalidLeadingOperation(tokens.front().Operation))
        {
            tokens.erase(tokens.begin());
        }     
        while (!tokens.empty() && IsInvalidTrailingOperation(tokens.back().Operation))
        {
            tokens.pop_back();
        }
    }

    static bool IsInvalidLeadingOperation(WordOperations operation)
    {        
        return operation == WordOperations::OR || operation == WordOperations::AND;
    }

    static bool IsInvalidTrailingOperation(WordOperations operation)
    {       
        return operation != WordOperations::None && operation != WordOperations::CloseParenthesis;
    }

    static void CorrectOperationSequencesAndAddDefaultAND(std::vector<WordStruct>& tokens)
    {
        for (int i = 0; i < tokens.size() - 1; i++)
        {           
            CorrectOperationSequence(tokens,  i);           
            InsertDefaultAND(tokens, i);
        }
    }
  
	static void CorrectOperationSequence(std::vector<WordStruct>& tokens, int& i) {
		if (IsOperation(tokens[i].Operation) && IsOperation(tokens[i + 1].Operation)) {
			if (tokens[i].Operation != WordOperations::NOT && tokens[i + 1].Operation == WordOperations::NOT) {
				return;
			}
			if (tokens[i].Operation == WordOperations::NOT && tokens[i + 1].Operation == WordOperations::NOT) {				
				tokens.erase(tokens.begin() + i + 1);
				return;
			}
			
			tokens[i] = WordStruct{ tokens[i].Word, WordOperations::AND };
			tokens.erase(tokens.begin() + i + 1);
			i--;
		}
	}


    void InsertDefaultAND(std::vector<WordStruct>& tokens, int i) {
        bool isNotWithoutConnector = (tokens[i + 1].Operation == WordOperations::NOT) &&
            (i == 0 || (!IsConnector(tokens[i].Operation) && tokens[i].Operation != WordOperations::CloseParenthesis));

        if (!IsOperation(tokens[i].Operation) && (!IsOperation(tokens[i + 1].Operation) || isNotWithoutConnector)) {
            tokens.insert(tokens.begin() + i + 1, { std::vector<char32_t>(), WordOperations::AND });
        }
    }

    static bool IsConnector(WordOperations operation)
    {
        return operation == WordOperations::AND || operation == WordOperations::OR;
    }

    static bool AreParenthesesValid(const std::vector<WordStruct>& tokens)
    {
        int openParenthesesCount = 0;
        for (const auto& token : tokens)
        {
            if (token.Operation == WordOperations::OpenParenthesis)
            {
                openParenthesesCount++;
            }
            else if (token.Operation == WordOperations::CloseParenthesis)
            {
                openParenthesesCount--;
                if (openParenthesesCount < 0)
                {                    
                    return false;
                }
            }
        }
        return openParenthesesCount == 0; 
    }

    static void RemoveAllParentheses(std::vector<WordStruct>& tokens) {
        std::erase_if(tokens, [](const WordStruct& token) {
            return token.Operation == WordOperations::OpenParenthesis ||
                token.Operation == WordOperations::CloseParenthesis;
            });
    }

	static bool IsOperation(WordOperations operation)
	{
		return operation != WordOperations::None;
	}

}