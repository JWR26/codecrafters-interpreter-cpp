#include "tokenizer.h"

namespace CPPlox {

    Tokens tokenize(const std::string& file) {
        Tokens tokens{};
        tokens.reserve(file.size());

        std::string::const_iterator it = file.begin();

        while(it != file.end()){
            switch (*it) {
                case '(':
                    tokens.emplace_back(TOKEN_TYPE::LEFT_PAREN, std::string(it, it));
                    break;
                case ')':
                    tokens.emplace_back(TOKEN_TYPE::RIGHT_PAREN, std::string(it, it));
                    break;
                default:
                    break;
            }
            
            ++it;  
        };

        return tokens;
    }

    void print_token(const Token& t){
        std::cout << TOKEN_STRING[t.tokentype] << ' ' << t.lexeme << ' ' << '\n';
    }
}