#ifndef PARSER
#define PARSER

#include <iostream>
#include <memory>
#include <string>
#include <variant>

#include "tokenizer.h"

namespace cpplox {

    struct Expression{
    };

    using Expr_ptr = std::shared_ptr<Expression>;

    struct literal : Expression {
        std::variant<std::string, double, bool> string, number, boolean;

        literal(const std::string& str){
            string = str;
        }

        literal(const double& num){
            number = num;
        }

        literal(const bool& b){
            std::cerr << "initialised a boolean literal";
            boolean = b;
        }

        friend std::ostream& operator<<(std::ostream& os, const literal& expr) {
            std::cerr << "calling ostream on literal...";
            os << "Literal Expression";
            return os;
        }
    };

    struct unary : Expression {
        std::shared_ptr<Token> op;
        std::shared_ptr<unary> right;

        friend std::ostream& operator<<(std::ostream& os, const unary& expr) {
            os << "Unary Expression\n";
            return os;
        }
    };

    struct binary : Expression {
        Expr_ptr left;
        std::shared_ptr<Token> op;
        Expr_ptr right;

        friend std::ostream& operator<<(std::ostream& os, const binary& expr) {
            os << "Binary Expression\n";
            return os;
        }
    };

    struct grouping : Expression {
        Expr_ptr expr;
        
        friend std::ostream& operator<<(std::ostream& os, const grouping& expr) {
            os << "Grouping Expression\n";
            return os;
        }
    };

    Expr_ptr expression(Tokens_iterator& it);

    Expr_ptr equality(Tokens_iterator& it);

    Expr_ptr comparison(Tokens_iterator& it);

    Expr_ptr term(Tokens_iterator& it);

    Expr_ptr factor(Tokens_iterator& it);

    Expr_ptr unary(Tokens_iterator& it);

    Expr_ptr primary(Tokens_iterator& it);
    
    Expr_ptr parse(const Tokens& tokens);

}

#endif