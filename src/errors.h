#ifndef ERRORS
#define ERRORS

#include <iostream>

namespace cpplox {
    namespace errors {
        
        static int exit_code {0};

        void unexpected_character(const int& line, const char& c);

    }

}
#endif