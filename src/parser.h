#ifndef PARSER
#define PARSER

#include <memory>

#include "tokenizer.h"

namespace cpplox {

    struct Expression{
        virtual std::ostream& operator<<(std::ostream& os) = 0;
    };

    using Expr_ptr = std::shared_ptr<Expression>;

    struct literal : Expression {
        std::shared_ptr<Token> value;

        std::ostream& operator<<(std::ostream& os) override {
            os << "Literal Expression";
            return os;
        }
    };

    struct unary : Expression {
        std::shared_ptr<Token> op;
        std::shared_ptr<unary> right;

        std::ostream& operator<<(std::ostream& os) override {
            os << "Unary Expression\n";
            return os;
        }
    };

    struct binary : Expression {
        Expr_ptr left;
        std::shared_ptr<Token> op;
        Expr_ptr right;

        std::ostream& operator<<(std::ostream& os) override {
            os << "Binary Expression\n";
            return os;
        }
    };

    struct grouping : Expression {
        Expr_ptr expr;
        
        std::ostream& operator<<(std::ostream& os) override {
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