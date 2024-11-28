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
                    tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::LEFT_PAREN, it, 1, line));
                    break;
                case ')':
                    tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::RIGHT_PAREN, it, 1, line));
                    break;
                case '{':
                    tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::LEFT_BRACE, it, 1, line));
                    break;
                case '}':
                    tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::RIGHT_BRACE, it, 1, line));
                    break;
                case ',':
                    tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::COMMA, it, 1, line));
                    break;
                case '.':
                    tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::DOT, it, 1, line));
                    break;
                case '-':
                    tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::MINUS, it, 1, line));
                    break;
                case '+':
                    tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::PLUS, it, 1, line));
                    break;
                case ';':
                    tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::SEMICOLON, it, 1, line));
                    break;
                case '*':
                    tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::STAR, it, 1, line));
                    break;
                case '=':
                    if (next(it) == '=') {
                        tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::EQUAL_EQUAL, it, 2, line));
                        ++it;
                    }
                    else {
                        tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::EQUAL, it, 1, line));
                    }
                    break;
                case '!':
                    if (next(it) == '=') {
                        tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::BANG_EQUAL, it, 2, line));
                        ++it;
                    }
                    else {
                        tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::BANG, it, 1, line));
                    }
                    break;
                case '<':
                    if (next(it) == '=') {
                        tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::LESS_EQUAL, it, 2, line));
                        ++it;
                    }
                    else {
                        tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::LESS, it, 1, line));
                    }
                    break;
                case '>':
                    if (next(it) == '=') {
                        tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::GREATER_EQUAL, it, 2, line));
                        ++it;
                    }
                    else {
                        tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::GREATER, it, 1, line));
                    }
                    break;
                case '/':
                    if (next(it) == '/') {
                        while (next(it) != '\n' && next(it) != '\0'){
                            ++it;
                        }
                    }
                    else {
                        tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::SLASH, it, 1, line));
                    }
                    break;
                case ' ':
                    break;
                case '\r':
                    break;
                case '\t':
                    break;
                case '\n':
                    ++line;
                    break;
                case '"': {
                    std::string::const_iterator temp = it;
                    size_t start_line{line}; 

                    while (next(temp) != '"' && next(temp) != '\0'){
                        if (next(temp) == '\n'){
                            ++line;
                        }
                        ++temp;
                    }
                    if (next(temp) == '\0') {
                        errors::unterminated_string(line);
                    } else {
                        std::shared_ptr<Token> t = std::make_shared<Token>(TOKEN_TYPE::STRING, it, std::distance(it, temp) + 1, start_line);
                        t->string = "TEST";
                        tokens.push_back(t);
                        ++temp;
                    }
                    it = temp;
                    break;
                }
                default:
                    errors::unexpected_character(line, *it);
                    break;
            }
            
            ++it;  
        };

        tokens.emplace_back(std::make_shared<Token>(TOKEN_TYPE::END_OF_FILE, it, 0, line));

        return tokens;
    }

}