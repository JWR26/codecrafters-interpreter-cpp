#include "parser.h"

namespace cpplox{

    Expr_ptr expression(Tokens_iterator& it){
        return equality(it);
    }

    Expr_ptr equality(Tokens_iterator& it){
        Expr_ptr expr = comparison(it);
        // factor will move the pointer, no need to increment for the term
        while((*it)->tokentype == TOKEN_TYPE::BANG_EQUAL || (*it)->tokentype == TOKEN_TYPE::EQUAL_EQUAL){
            Token_ptr op = *it;
            Expr_ptr right = comparison(++it);
            expr = std::make_shared<Binary>(expr, op, right);
        }
        
        return expr;
    }

    Expr_ptr comparison(Tokens_iterator& it){
        Expr_ptr expr = term(it);
        // factor will move the pointer, no need to increment for the term
        while((*it)->tokentype == TOKEN_TYPE::GREATER || (*it)->tokentype == TOKEN_TYPE::GREATER_EQUAL || (*it)->tokentype == TOKEN_TYPE::LESS || (*it)->tokentype == TOKEN_TYPE::LESS_EQUAL){
            Token_ptr op = *it;
            Expr_ptr right = term(++it);
            expr = std::make_shared<Binary>(expr, op, right);
        }
        
        return expr;
    }

    Expr_ptr term(Tokens_iterator& it){
        Expr_ptr expr = factor(it);
        // factor will move the pointer, no need to increment for the term
        while((*it)->tokentype == TOKEN_TYPE::MINUS || (*it)->tokentype == TOKEN_TYPE::PLUS){
            Token_ptr op = *it;
            Expr_ptr right = factor(++it);
            expr = std::make_shared<Binary>(expr, op, right);
        }
        
        return expr;
    }

    Expr_ptr factor(Tokens_iterator& it){
        Expr_ptr expr = unary(it);
        ++it;

        while((*it)->tokentype == TOKEN_TYPE::SLASH || (*it)->tokentype == TOKEN_TYPE::STAR){
            Token_ptr op = *it;
            Expr_ptr right = unary(++it);
            expr = std::make_shared<Binary>(expr, op, right);
            ++it;
        }
        
        return expr;
    }

    Expr_ptr unary(Tokens_iterator& it){
        if((*it)->tokentype == TOKEN_TYPE::BANG || (*it)->tokentype == TOKEN_TYPE::MINUS){
            Token_ptr t_ptr = *it;
            Expr_ptr right = unary(++it);
            return std::make_shared<Unary>(t_ptr, right);
        }
        return primary(it);
    }

    Expr_ptr primary(Tokens_iterator& it){
        if ((*it)->tokentype == TOKEN_TYPE::TRUE){
            return std::make_shared<Literal>(true);
        }
        if ((*it)->tokentype == TOKEN_TYPE::FALSE){
            return std::make_shared<Literal>(false);
        }
        if ((*it)->tokentype == TOKEN_TYPE::NUMBER){
            return std::make_shared<Literal>(std::get<double>((*it)->number));
        }
        if ((*it)->tokentype == TOKEN_TYPE::STRING){
            return std::make_shared<Literal>(std::get<std::string>((*it)->string));
        }

        if((*it)->tokentype == TOKEN_TYPE::LEFT_PAREN){
            std::cerr << "Parsing grouping... ";
            Expr_ptr expr = std::make_shared<grouping>(expression(++it));
            if ((*it)->tokentype != TOKEN_TYPE::RIGHT_PAREN){
                errors::exit_code = 65;
                throw std::exception();
            }
            return expr;
        }
        
        errors::exit_code = 65;
        throw std::exception();
    }
    
    Expr_ptr parse(const Tokens& tokens){
        Tokens_iterator it = tokens.begin();
        try{
            return expression(it);
        }
        catch (...){
            std::cerr << "Exception caught\n";
            std::exit(65);
            return nullptr;
        }
    }

}