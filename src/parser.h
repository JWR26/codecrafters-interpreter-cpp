#ifndef PARSER
#define PARSER

#include <iostream>
#include <memory>
#include <string>
#include <variant>

#include "tokenizer.h"

namespace cpplox {

    struct Expression{
        virtual std::ostream& print(std::ostream& os) const = 0;
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

        virtual std::ostream& print(std::ostream& os) const override {
            return os << "Literal Expression";
        }

        friend std::ostream& operator<<(std::ostream& os, const literal& expr) {
            return expr.print(os);
        }
    };

    struct unary : Expression {
        std::shared_ptr<Token> op;
        std::shared_ptr<unary> right;

        virtual std::ostream& print(std::ostream& os) const override {
            return os << "Unary Expression\n";
        }

        friend std::ostream& operator<<(std::ostream& os, const unary& expr) {
            return expr.print(os);
        }
    };

    struct binary : Expression {
        Expr_ptr left;
        std::shared_ptr<Token> op;
        Expr_ptr right;
        
        virtual std::ostream& print(std::ostream& os) const override {
            return os << "Binary Expression\n";
        }

        friend std::ostream& operator<<(std::ostream& os, const binary& expr) {
            return expr.print(os);
        }
    };

    struct grouping : Expression {
        Expr_ptr expr;
        
        virtual std::ostream& print(std::ostream& os) const override {
            return os << "Grouping Expression\n";
        }
        
        friend std::ostream& operator<<(std::ostream& os, const grouping& expr) {
            return expr.print(os);
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