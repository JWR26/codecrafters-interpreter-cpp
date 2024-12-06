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

        void unexpected_token(const int& line, const char& c) {
            std::cerr << "[line " << line << "] Error at '" << c << "': Expect expression.\n";
            exit_code = 65;
        }
    }

}