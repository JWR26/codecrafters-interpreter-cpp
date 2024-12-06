#include "errors.h"

namespace cpplox {

    namespace errors {
        
        int get_exit_code(){
            return exit_code;
        }

        void unexpected_character(const int& line, const char& c) {
            std::cerr << "[line " << line << "] Error: Unexpected character: " << c << "\n";
            exit_code = 65;
        }

        void unterminated_string(const int& line){
            std::cerr << "[line " << line << "] Error: Unterminated string.";
            exit_code = 65;
        }

        void unexpected_token(const int& line, const std::shared_ptr<Token>& t) {
            if (t->tokentype == TOKEN_TYPE::END_OF_FILE){
                std::cerr << "[line " << t->line << "] Error at end. Expect expression.\n";
            } else {
                std::cerr << "[line " << t->line << "] Error at '";
                t->print_lexeme(std::cerr);
                std::cerr << "': Expect expression";
            }
            
            exit_code = 65;
        }
    }

}