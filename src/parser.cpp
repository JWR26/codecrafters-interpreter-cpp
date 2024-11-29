#include "parser.h"

namespace cpplox{

    Expr_ptr expression(Tokens_iterator& it){
        return equality(it);
    }

    Expr_ptr equality(Tokens_iterator& it){
        return comparison(it);
    }

    Expr_ptr comparison(Tokens_iterator& it){
        return term(it);
    }

    Expr_ptr term(Tokens_iterator& it){
        return factor(it);
    }

    Expr_ptr factor(Tokens_iterator& it){
        return unary(it);
    }

    Expr_ptr unary(Tokens_iterator& it){
        return primary(it);
    }

    Expr_ptr primary(Tokens_iterator& it){
        if ((*it)->tokentype == TOKEN_TYPE::TRUE){
            return std::make_shared<literal>(true);
        }
        if ((*it)->tokentype == TOKEN_TYPE::FALSE){
            return std::make_shared<literal>(false);
        }
        if ((*it)->tokentype == TOKEN_TYPE::NUMBER){
            return std::make_shared<literal>((*it)->number);
        }
        return std::make_shared<literal>();
    }
    
    Expr_ptr parse(const Tokens& tokens){
        Tokens_iterator it = tokens.begin();
        return expression(it);
    }

}