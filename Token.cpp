#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
    // TODO: initialize all member variables
    this->line = line;
    this->type = type;
    this->description = description;
}

std::string Token::toString() {
//    if(this->type == TokenType::STRING) {
//        return "(" + this->tokenTypeToString() + ",\"" + this->description.substr(1,this->description.size()) + "\"," + std::to_string(this->line) + ")";
//    }
    return "(" + this->tokenTypeToString() + ",\"" + this->description + "\"," + std::to_string(this->line) + ")";
}

std::string Token::getInfo() {
    return this->description;
}

std::string Token::tokenTypeToString() {
    TokenType tType = this->type;
    std::string outString = "ERROR";
    switch (tType) {
        case TokenType::COLON :
            outString = "COLON";
            break;
        case TokenType::COLON_DASH :
            outString = "COLON_DASH";
            break;
        case TokenType::COMMA :
            outString = "COMMA";
            break;
        case TokenType::PERIOD :
            outString = "PERIOD";
            break;
        case TokenType::Q_MARK :
            outString = "Q_MARK";
            break;
        case TokenType::LEFT_PAREN :
            outString = "LEFT_PAREN";
            break;
        case TokenType::RIGHT_PAREN :
            outString = "RIGHT_PAREN";
            break;
        case TokenType::MULTIPLY :
            outString = "MULTIPLY";
            break;
        case TokenType::ADD :
            outString = "ADD";
            break;
        case TokenType::SCHEMES :
            outString = "SCHEMES";
            break;
        case TokenType::FACTS :
            outString = "FACTS";
            break;
        case TokenType::RULES :
            outString = "RULES";
            break;
        case TokenType::QUERIES :
            outString = "QUERIES";
            break;
        case TokenType::ID :
            outString = "ID";
            break;
        case TokenType::STRING :
            outString = "STRING";
            break;
        case TokenType::COMMENT :
            outString = "COMMENT";
            break;
        case TokenType::EOF_TYPE :
            outString = "EOF";
            break;
        case TokenType::UNDEFINED :
            outString = "UNDEFINED";
            break;
    }
    return outString;
}