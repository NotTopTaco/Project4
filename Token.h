#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COLON,
    COLON_DASH,
    // TODO: add the other types of tokens - DID
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    EOF_TYPE,
    UNDEFINED
};

class Token
{
private:
    // TODO: add member variables for information needed by Token
    TokenType type;
    std::string description;
    int line;

public:
    //description is the actual string value like ":-" "-" etc
    Token(TokenType type, std::string description, int line);
    std::string toString();
    std::string tokenTypeToString();
    std::string getInfo();

    // TODO: add other needed methods
};

#endif // TOKEN_H

