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

    using Token_ptr = std::shared_ptr<Token>;

    using Expr_ptr = std::shared_ptr<Expression>;

    struct Literal : Expression {
        std::variant<std::string, double, bool> string, number, boolean;

        Literal() {}

        Literal(const std::string& str){
            string = str;
        }

        Literal(const double& num){
            number = num;
        }

        Literal(const bool& b){
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

    struct Unary : Expression {
        Token_ptr op;
        Expr_ptr right;

        Unary(const Token_ptr& _op, const Expr_ptr& _right){
            op = _op;
            right = _right;
        }

        virtual std::ostream& print(std::ostream& os) const override {
            os << '(' <<*op->lexeme << ' ';
            right->print(os);
            return os << ')';
        }

    };

    struct Binary : Expression {
        Expr_ptr left;
        Token_ptr op;
        Expr_ptr right;

        Binary(const Expr_ptr& _left, const Token_ptr& _op, const Expr_ptr& _right){
            left = _left;
            op = _op;
            right = _right;
        }
        
        virtual std::ostream& print(std::ostream& os) const override {
            os << '(' << *op->lexeme << ' ';
            left->print(os);
            os << ' ';
            right->print(os);
            return os << ')';
        }

    };

    struct grouping : Expression {
        Expr_ptr expr;

        grouping(const Expr_ptr& _expr){
            expr = _expr;
        }
        
        virtual std::ostream& print(std::ostream& os) const override {
            os << "(group ";
            expr->print(os);
            return os << ')';
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