#include "tokenizer.h"

// TODO: Document code for clarity
namespace CPPlox {

    Tokens tokenize(const std::string& file) {
        Tokens tokens{};
        tokens.reserve(file.size());

        std::string::const_iterator it = file.begin();

        size_t line{1};

        while(it != file.end()){
            switch (*it) {
                case '(':
                    tokens.emplace_back(TOKEN_TYPE::LEFT_PAREN, std::string(1, *it), line);
                    break;
                case ')':
                    tokens.emplace_back(TOKEN_TYPE::RIGHT_PAREN, std::string(1, *it), line);
                    break;
                case '{':
                    tokens.emplace_back(TOKEN_TYPE::LEFT_BRACE, std::string(1, *it), line);
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