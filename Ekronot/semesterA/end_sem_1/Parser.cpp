#include "Parser.h"
#include <iostream>
#include "IndentationException.h"
#include "SyntaxException.h"
#include "NameErrorException.h"

#include "Sequence.h"
#include "Boolean.h"
#include "Integer.h"
#include "String.h"
#include "Type.h"
#include "Void.h"

std::unordered_map<std::string, Type*> Parser::variables;

Type* Parser::parseString(std::string str)
{   
    try {
        Helper::trim(str);
        if (str.empty()) return nullptr;

        if (str.find('=') != std::string::npos) {
            if (makeAssignment(str)) {
                return new Void(true);
            }
        }

        Type* directType = getType(str);
        if (directType != nullptr) return directType;

        return getVariableValue(str);

    } catch (const NameErrorException& e) {
        throw; 
    } catch (...) {
        throw SyntaxException();
    }
}

Type* Parser::getType(std::string str)
{
    Helper::trim(str);

    if (Helper::isInteger(str)) {
        return new Integer(std::stoi(str), true);
    }
    else if (Helper::isBoolean(str)) {
        if (str == "true" || str == "True") {
            return new Boolean(true, true);
        }
        else {
            return new Boolean(false, true);
        }
    }
    else if (Helper::isString(str)) {
        std::string value = str.substr(1, str.size() - 2);
        return new String(value, true);
    }
    else {
        return nullptr;
    }
}

bool Parser::isLegalVarName(std::string str)
{
    if (str.empty()) {
        return false;
    }

    if (!(Helper::isLetter(str[0]) || Helper::isUnderscore(str[0]))) {
        return false;
    }

    for (char c : str) {
        if (!(Helper::isLetter(c) || Helper::isDigit(c) || Helper::isUnderscore(c))) {
            return false;
        }
    }

    return true;
}

bool Parser::makeAssignment(std::string str)
{
    size_t equalPos = str.find('=');
    if (equalPos == std::string::npos) return false;

    std::string varName = str.substr(0, equalPos);
    std::string rhs = str.substr(equalPos + 1);
    Helper::trim(varName);
    Helper::trim(rhs);

    if (!isLegalVarName(varName)) {
        throw NameErrorException("NameError: invalid identifier '" + varName + "'");
    }

    Type* newValue = nullptr;

    newValue = getType(rhs);

    if (newValue == nullptr) {
        auto itSource = variables.find(rhs);
        if (itSource != variables.end()) {
            Type* sourcePtr = itSource->second;
    
            if (auto* i = dynamic_cast<Integer*>(sourcePtr)) {
                newValue = new Integer(i->getValue(), true); 
            }
            else if (auto* s = dynamic_cast<String*>(sourcePtr)) {
                newValue = new String(s->getValue(), true);
            }
            else if (auto* b = dynamic_cast<Boolean*>(sourcePtr)) {
                newValue = new Boolean(b->getValue(), true);
            }
    
        } else {
            throw NameErrorException("NameError: name '" + rhs + "' is not defined");
        }
    }

    auto itOld = variables.find(varName);
    if (itOld != variables.end()) {
        delete itOld->second; 
    }

    newValue->setTemp(false); 
    variables[varName] = newValue;
    
    return true;
}

Type* Parser::getVariableValue(std::string str)
{
    Helper::trim(str);
    auto it = variables.find(str);
    if (it != variables.end()) {
        return it->second;
    }
    else {
        std::string errorMsg = "NameError: name \'" + str + "\' is not defined";
        throw NameErrorException(errorMsg);
    }
}

bool Parser::deleteVariable(std::string varName)
{
    Helper::trim(varName);
    auto it = variables.find(varName);
    if (it != variables.end()) {
        delete it->second;
        variables.erase(it);
        return true;
    }
    return false;
}

void Parser::clearVariables()
{
    for (auto const& [name, typePtr] : variables) 
    {
        delete typePtr;
    }
    variables.clear();
}

bool Parser::copyVariable(std::string str)
{
    Helper::trim(str);
    size_t copyPos = str.find('=');
    if (copyPos == std::string::npos) return false;

    std::string varName = str.substr(0, copyPos);
    std::string sourceVarName = str.substr(copyPos + 1);
    Helper::trim(varName);
    Helper::trim(sourceVarName);

    auto it = variables.find(sourceVarName);
    if (it != variables.end()) {
        return makeAssignment(str); 
    }
    else {
        throw NameErrorException("NameError: name '" + sourceVarName + "' is not defined");
    }
}