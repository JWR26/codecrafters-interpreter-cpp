#ifndef ERRORS
#define ERRORS

#include <iostream>

#include "tokenizer.h"
// add docstrings

namespace cpplox {
    namespace errors {
        
        static int exit_code {0};

        int get_exit_code();

        void unexpected_character(const int& line, const char& c);

        void unterminated_string(const int& line);

        void unexpected_token(const int& line, const std::shared_ptr<cpplox::Token>& t);
        
    }

}
#endif