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
                    break;
                case '}':
                    tokens.emplace_back(TOKEN_TYPE::RIGHT_BRACE, std::string(1, *it), line);
                    break;
                case ',':
                    tokens.emplace_back(TOKEN_TYPE::COMMA, std::string(1, *it), line);
                    break;
                case '.':
                    tokens.emplace_back(TOKEN_TYPE::DOT, std::string(1, *it), line);
                    break;
                case '-':
                    tokens.emplace_back(TOKEN_TYPE::MINUS, std::string(1, *it), line);
                    break;
                case '+':
                    tokens.emplace_back(TOKEN_TYPE::PLUS, std::string(1, *it), line);
                    break;
                case ';':
                    tokens.emplace_back(TOKEN_TYPE::SEMICOLON, std::string(1, *it), line);
                    break;
                case '*':
                    tokens.emplace_back(TOKEN_TYPE::STAR, std::string(1, *it), line);
                    break;
                default:
                    break;
            }
            
            ++it;  
        };

        tokens.emplace_back(TOKEN_TYPE::END_OF_FILE, std::string(""), line);

        return tokens;
    }

}