#ifndef ERRORS
#define ERRORS

#include <iostream>

// add docstrings

namespace cpplox {
    namespace errors {
        
        static int exit_code {0};

        void unexpected_character(const int& line, const char& c);

        int get_exit_code();

    }

}
#endif