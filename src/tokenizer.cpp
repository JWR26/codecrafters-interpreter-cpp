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
                case '\r':
                case '\t':
                    break;
                case '\n':
                    ++line;
                    break;
                case '"': {
                    std::cerr << "creating string\n";
                    std::string::const_iterator start = it;
                    size_t start_line{line}; 

                    while (next(it) != '"' && next(it) != '\0'){
                        std::cerr << *it;
                        if (next(it) == '\n'){
                            ++line;
                        }
                        ++it;
                    }
                    if (next(it) == '\0') {
                        errors::unterminated_string(line);
                    } else {
                        ++it;
                        std::shared_ptr<Token> t = std::make_shared<Token>(TOKEN_TYPE::STRING, start, std::distance(start, it) + 1, start_line);
                        t->string = std::string(it+1, it);
                        tokens.push_back(t);
                    }
                    break;
                }
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9': {
                // placeholder for nubmer logic
                    double number{0};
                    std::string::const_iterator start = it;
                    
                    while (isdigit(*it)) {
                        number *= 10;
                        number += *it - '0';
                        ++it;
                    }
                    if (*it == '.') {
                        ++it;
                        double decimal {0};
                        double divisor {10};
                        while (isdigit(*it)) {
                            number += (*it - '0') / divisor;
                            divisor *= 10;
                            ++it;
                        }
                        number += decimal;
                    }

                    std::shared_ptr<Token> t = std::make_shared<Token>(TOKEN_TYPE::NUMBER, start, std::distance(start, it), line);
                    t->number = number;
                    tokens.push_back(t);
                    --it;
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