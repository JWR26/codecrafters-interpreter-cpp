#include "tokenizer.h"

// TODO: Document code for clarity
namespace cpplox {

    char next(const std::string::const_iterator& it){
        return *(it + 1);
    }

    Tokens tokenize(const std::string& file) {
        Tokens tokens{};
        tokens.reserve(file.size());

        std::string::const_iterator it = file.begin();

        size_t line{1};

        while(it != file.end()){
            switch (*it) {
                case '(':
                    tokens.emplace_back(TOKEN_TYPE::LEFT_PAREN, it, 1, line);
                    break;
                case ')':
                    tokens.emplace_back(TOKEN_TYPE::RIGHT_PAREN, it, 1, line);
                    break;
                case '{':
                    tokens.emplace_back(TOKEN_TYPE::LEFT_BRACE, it, 1, line);
                    break;
                case '}':
                    tokens.emplace_back(TOKEN_TYPE::RIGHT_BRACE, it, 1, line);
                    break;
                case ',':
                    tokens.emplace_back(TOKEN_TYPE::COMMA, it, 1, line);
                    break;
                case '.':
                    tokens.emplace_back(TOKEN_TYPE::DOT, it, 1, line);
                    break;
                case '-':
                    tokens.emplace_back(TOKEN_TYPE::MINUS, it, 1, line);
                    break;
                case '+':
                    tokens.emplace_back(TOKEN_TYPE::PLUS, it, 1, line);
                    break;
                case ';':
                    tokens.emplace_back(TOKEN_TYPE::SEMICOLON, it, 1, line);
                    break;
                case '*':
                    tokens.emplace_back(TOKEN_TYPE::STAR, it, 1, line);
                    break;
                case '=':
                    if (next(it) == '=') {
                        tokens.emplace_back(TOKEN_TYPE::BANG_EQUAL, it, 2, line);
                        ++it;
                    }
                    else {
                        tokens.emplace_back(TOKEN_TYPE::EQUAL, it, 1, line);
                    }
                    break;
                default:
                    errors::unexpected_character(line, *it);
                    break;
            }
            
            ++it;  
        };

        tokens.emplace_back(TOKEN_TYPE::END_OF_FILE, std::string(""), line);

        return tokens;
    }

}