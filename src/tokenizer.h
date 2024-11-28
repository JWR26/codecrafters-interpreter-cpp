#ifndef TOKENIZER
#define TOKENIZER

#include <array>
#include <iostream>
#include <memory>
#include <string>
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

    struct Token{
        enum TOKEN_TYPE tokentype;
        std::string::const_iterator lexeme;
        size_t length;
        size_t line;
        
        std::variant<double, std::string> number, string;

        Token() {}

        Token(
            const TOKEN_TYPE& type, 
            const std::string::const_iterator& lexeme, 
            const size_t& length, 
            const size_t& line, 
            const std::string& string
            ) : tokentype(type),
            lexeme(lexeme), 
            length(length), 
            line(line),
            string(string) {}

        friend std::ostream& operator<<(std::ostream& os, const Token& t) {
            os << TOKEN_STRING[t.tokentype] << ' ';
            
            for (size_t i = 0; i < t.length; ++i){
                os << *(t.lexeme + i);
            }

            os << ' ';

            if (t.tokentype == TOKEN_TYPE::NUMBER) {
                os << std::get<double>(t.number);
            } else if (t.tokentype == TOKEN_TYPE::STRING) {
                os << std::get<std::string>(t.string);
            } else {
                os << "null";
            }
            os << '\n';

            return os;
        }
    };

    using Tokens = std::vector<std::shared_ptr<Token>>;

    Tokens tokenize(const std::string& file);

    char next(const std::string::const_iterator& it);

}

#endif