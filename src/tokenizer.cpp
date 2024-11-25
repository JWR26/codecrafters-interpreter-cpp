#include "tokenizer.h"

namespace CPPlox {

    Tokens tokenize(const std::string& file) {
        Tokens tokens{};

        return tokens;
    }

    void print_token(const Token& t){
        std::cout << TOKEN_STRING[t.tokentype] << ' ' << t.lexeme << ' ' << '\n';
    }
}