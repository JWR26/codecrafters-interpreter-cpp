#include "errors.h"

namespace cpplox {

    namespace errors {
        
        void unexpected_character(const int& line, const char& c) {
            std::cout << "[line " << line << "] Error: Unexpected character: " << c << "\n";
        }

    }

}