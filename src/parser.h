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

        literal() {}

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
            if (std::get_if<bool>(&boolean)){
                os << std::boolalpha;
                return os << std::get<bool>(boolean);
            }

            if (std::get_if<double>(&number)){
                double integral;
                double decimal = std::modf(std::get<double>(number), &integral);
                if (decimal == 0.0) {
                    os << integral << '.' << '0';
                } else {
                    os << std::get<double>(number);
                }
                return os;
            }

            if (std::get<std::string>(string).empty()){
                return os << "nil";
            }

            return os << std::get<std::string>(string);
        }

    };

    struct unary : Expression {
        std::shared_ptr<Token> op;
        std::shared_ptr<unary> right;

        virtual std::ostream& print(std::ostream& os) const override {
            return os << "Unary Expression\n";
        }

    };

    struct binary : Expression {
        Expr_ptr left;
        std::shared_ptr<Token> op;
        Expr_ptr right;
        
        virtual std::ostream& print(std::ostream& os) const override {
            return os << "Binary Expression\n";
        }

    };

    struct grouping : Expression {
        Expr_ptr expr;
        
        virtual std::ostream& print(std::ostream& os) const override {
            return os << "Grouping Expression\n";
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