#include "ExpressionEvaluator.h"
#include <algorithm>

ExpressionEvaluator::ExpressionEvaluator() {
    // Initialize default variables
    variables["pi"] = 3.14159265f;
    variables["e"] = 2.71828182f;
}

void ExpressionEvaluator::setVariable(const std::string& name, float value) {
    variables[name] = value;
}

float ExpressionEvaluator::evaluate(const std::string& expression) {
    return parseExpression(expression);
}

float ExpressionEvaluator::parseExpression(const std::string& expr) {
    size_t pos = 0;
    return parseTerm(expr, pos);
}

float ExpressionEvaluator::parseTerm(const std::string& expr, size_t& pos) {
    float result = parseFactor(expr, pos);
    
    while (pos < expr.length()) {
        skipWhitespace(expr, pos);
        
        if (pos >= expr.length()) break;
        
        char op = expr[pos];
        if (op == '+' || op == '-') {
            pos++;
            float right = parseFactor(expr, pos);
            result = (op == '+') ? result + right : result - right;
        } else {
            break;
        }
    }
    
    return result;
}

float ExpressionEvaluator::parseFactor(const std::string& expr, size_t& pos) {
    float result = parseNumber(expr, pos);
    
    while (pos < expr.length()) {
        skipWhitespace(expr, pos);
        
        if (pos >= expr.length()) break;
        
        char op = expr[pos];
        if (op == '*' || op == '/' || op == '%') {
            pos++;
            float right = parseNumber(expr, pos);
            if (op == '*') {
                result *= right;
            } else if (op == '/') {
                result = (right != 0) ? result / right : 0;
            } else if (op == '%') {
                result = (int)result % (int)right;
            }
        } else {
            break;
        }
    }
    
    return result;
}

float ExpressionEvaluator::parseNumber(const std::string& expr, size_t& pos) {
    skipWhitespace(expr, pos);
    
    if (pos >= expr.length()) return 0;
    
    // Handle parentheses
    if (expr[pos] == '(') {
        pos++;
        float result = parseTerm(expr, pos);
        if (pos < expr.length() && expr[pos] == ')') {
            pos++;
        }
        return result;
    }
    
    // Handle variables and identifiers
    if (isLetter(expr[pos])) {
        std::string identifier = extractIdentifier(expr, pos);
        
        // Check if it's a function call
        skipWhitespace(expr, pos);
        if (pos < expr.length() && expr[pos] == '(') {
            pos++;
            float arg = parseTerm(expr, pos);
            if (pos < expr.length() && expr[pos] == ')') {
                pos++;
            }
            
            // Simple math functions
            if (identifier == "sin") return std::sin(arg);
            if (identifier == "cos") return std::cos(arg);
            if (identifier == "tan") return std::tan(arg);
            if (identifier == "sqrt") return std::sqrt(arg);
            if (identifier == "abs") return std::abs(arg);
            if (identifier == "floor") return std::floor(arg);
            if (identifier == "ceil") return std::ceil(arg);
        }
        
        // Variable lookup
        if (variables.find(identifier) != variables.end()) {
            return variables[identifier];
        }
        
        return 0;
    }
    
    // Handle numeric literals
    float number = 0;
    bool hasDecimal = false;
    float decimalPlace = 0.1f;
    
    while (pos < expr.length() && (isDigit(expr[pos]) || expr[pos] == '.')) {
        if (expr[pos] == '.') {
            if (hasDecimal) break;
            hasDecimal = true;
            pos++;
        } else {
            if (hasDecimal) {
                number += (expr[pos] - '0') * decimalPlace;
                decimalPlace *= 0.1f;
            } else {
                number = number * 10 + (expr[pos] - '0');
            }
            pos++;
        }
    }
    
    return number;
}

void ExpressionEvaluator::skipWhitespace(const std::string& expr, size_t& pos) {
    while (pos < expr.length() && std::isspace(expr[pos])) {
        pos++;
    }
}

bool ExpressionEvaluator::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

bool ExpressionEvaluator::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool ExpressionEvaluator::isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

std::string ExpressionEvaluator::extractIdentifier(const std::string& expr, size_t& pos) {
    std::string identifier;
    while (pos < expr.length() && (isLetter(expr[pos]) || isDigit(expr[pos]))) {
        identifier += expr[pos];
        pos++;
    }
    return identifier;
}
