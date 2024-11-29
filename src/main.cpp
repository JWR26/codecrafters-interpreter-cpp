#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

// headers to include
#include "parser.h"
#include "tokenizer.h"

std::string read_file_contents(const std::string& filename);

int main(int argc, char *argv[]) {
    // Disable output buffering
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    std::cerr << "Logs from your program will appear here!" << std::endl;

    if (argc < 3) {
        std::cerr << "Usage: ./your_program tokenize <filename>" << std::endl;
        return 1;
    }

    const std::string command = argv[1];

    std::string file_contents = read_file_contents(argv[2]);


    cpplox::Tokens tokens = cpplox::tokenize(file_contents);

    cpplox::Expr_ptr ast = cpplox::parse(tokens);

    if (command == "tokenize") {
        // print tokens
        for(const std::shared_ptr<cpplox::Token>& t: tokens){
            std::cout << *t;
        }
    } else if (command == "parse"){
        ast->print(std::cout);
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }

    return cpplox::errors::get_exit_code();
}

std::string read_file_contents(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error reading file: " << filename << std::endl;
        std::exit(1);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}
