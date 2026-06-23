#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

#include <string>
#include <unordered_map>
#include <cmath>
#include <cctype>
#include <sstream>

class ExpressionEvaluator {
public:
    ExpressionEvaluator();
    
    void setVariable(const std::string& name, float value);
    float evaluate(const std::string& expression);
    
private:
    std::unordered_map<std::string, float> variables;
    
    // Parsing helpers
    float parseExpression(const std::string& expr);
    float parseTerm(const std::string& expr, size_t& pos);
    float parseFactor(const std::string& expr, size_t& pos);
    float parseNumber(const std::string& expr, size_t& pos);
    
    // Utility
    void skipWhitespace(const std::string& expr, size_t& pos);
    bool isOperator(char c);
    bool isDigit(char c);
    bool isLetter(char c);
    std::string extractIdentifier(const std::string& expr, size_t& pos);
};

#endif // EXPRESSION_EVALUATOR_H
