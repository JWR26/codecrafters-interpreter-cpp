#ifndef TOKENIZER
#define TOKENIZER

#include <array>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

// add docstrings...

namespace CPPlox {
    
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
        std::string lexeme;
        size_t line;
        std::variant<double, std::string> number, string;

        friend std::ostream& operator<<(std::ostream& os, const Token& t){
            os << TOKEN_STRING[t.tokentype] << ' ' << t.lexeme << ' ';
            if (t.tokentype == TOKEN_TYPE::NUMBER){
                os << std::get<double>(t.number);
            } else if (t.tokentype == TOKEN_TYPE::STRING)
            {
                os << std::get<std::string>(t.string);
            } else{
                os << "null";
            }
            os << '\n';

            return os;
        }
    };

    using Tokens = std::vector<Token>;

    Tokens tokenize(const std::string& file);

    void print_token(const Token& t);
}

#endif