#ifndef TOKENIZER
#define TOKENIZER

#include <array>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "errors.h"

// add docstrings...

namespace cpplox {
    
    enum TOKEN_TYPE{
        LEFT_PAREN,
        RIGHT_PAREN,
        LEFT_BRACE,
        RIGHT_BRACE,
        COMMA,
        DOT,
        MINUS,
        PLUS,
        SEMICOLON,
        STAR,
        EQUAL,
        EQUAL_EQUAL,
        BANG,
        BANG_EQUAL,
        LESS,
        LESS_EQUAL,
        GREATER,
        GREATER_EQUAL,
        SLASH,
        // literals
        IDENTIFIER,
        STRING,
        NUMBER,
        // keywords
        AND,
        CLASS,
        ELSE,
        FALSE,
        FUN,
        FOR,
        IF,
        NIL,
        OR,
        PRINT,
        RETURN,
        SUPER,
        THIS,
        TRUE,
        VAR,
        WHILE,
        // end of file
        END_OF_FILE,
    };

    const std::array<std::string, 39> TOKEN_STRING {
        "LEFT_PAREN",
        "RIGHT_PAREN",
        "LEFT_BRACE",
        "RIGHT_BRACE",
        "COMMA",
        "DOT",
        "MINUS",
        "PLUS",
        "SEMICOLON",
        "STAR",
        "EQUAL",
        "EQUAL_EQUAL",
        "BANG",
        "BANG_EQUAL",
        "LESS",
        "LESS_EQUAL",
        "GREATER",
        "GREATER_EQUAL",
        "SLASH",
        "IDENTIFIER",
        "STRING",
        "NUMBER",
        "AND",
        "CLASS",
        "ELSE",
        "FALSE",
        "FUN",
        "FOR",
        "IF",
        "NIL",
        "OR",
        "PRINT",
        "RETURN",
        "SUPER",
        "THIS",
        "TRUE",
        "VAR",
        "WHILE",
        "EOF",
    };

    const std::unordered_map<std::string, TOKEN_TYPE> RESERVED_WORDS {
        {"and", TOKEN_TYPE::AND},
        {"class", TOKEN_TYPE::CLASS},
        {"else", TOKEN_TYPE::ELSE},
        {"false", TOKEN_TYPE::FALSE},
        {"for", TOKEN_TYPE::FOR},
        {"fun", TOKEN_TYPE::FUN},
        {"if", TOKEN_TYPE::IF},
        {"nil", TOKEN_TYPE::NIL},
        {"or", TOKEN_TYPE::OR},
        {"print", TOKEN_TYPE::PRINT},
        {"return", TOKEN_TYPE::RETURN},
        {"super", TOKEN_TYPE::SUPER},
        {"this", TOKEN_TYPE::THIS},
        {"true", TOKEN_TYPE::TRUE},
        {"var", TOKEN_TYPE::VAR},
        {"while", TOKEN_TYPE::WHILE}
    };

    struct Token{
        enum TOKEN_TYPE tokentype;
        std::string::const_iterator lexeme;
        size_t length;
        size_t line;
        
        std::variant<double, std::string> number, string;

        std::ostream& operator<<(std::ostream& os) {
            os << TOKEN_STRING[tokentype] << ' ';
            
            for (size_t i = 0; i < length; ++i){
                os << *(lexeme + i);
            }

            os << ' ';

            if (tokentype == TOKEN_TYPE::NUMBER) {
                double integral;
                double decimal = std::modf(std::get<double>(number), &integral);
                if (decimal == 0.0) {
                    os << integral << '.' << '0';
                } else {
                    os << std::get<double>(number);
                }
                
            } else if (tokentype == TOKEN_TYPE::STRING) {
                os << std::get<std::string>(string);
            } else {
                os << "null";
            }
            os << '\n';

            return os;
        }
    };

    using Tokens = std::vector<std::shared_ptr<Token>>;

    using Tokens_iterator = std::vector<std::shared_ptr<Token>>::const_iterator;

    Tokens tokenize(const std::string& file);

    char next(const std::string::const_iterator& it);
}

#endif