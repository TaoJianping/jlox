//
// Created by taojianping on 2019/9/18.
//

#ifndef JLOX_VISITOR_H
#define JLOX_VISITOR_H


#include "Expr.h"
#include <string>


template <typename T>
class Visitor {
    virtual T visitAssignExpr(Assign<std::any> expr) = 0;
    virtual T visitBinaryExpr(Binary<std::any> expr) = 0;
    virtual T visitCallExpr(Call<std::any> expr) = 0;
    virtual T visitGetExpr(Get<std::any> expr) = 0;
    virtual T visitSetExpr(Set<std::any> expr) = 0;
//    virtual T visitGroupingExpr(Grouping<std::any> expr) = 0;
//    virtual T visitLiteralExpr(Literal<std::any> expr) = 0;
//    virtual T visitLogicalExpr(Logical<std::any> expr) = 0;
//    virtual T visitSuperExpr(Super<std::any> expr) = 0;
//    virtual T visitThisExpr(This<std::any> expr) = 0;
//    virtual T visitUnaryExpr(Unary<std::any> expr) = 0;
//    virtual T visitVariableExpr(Variable<std::any> expr) = 0;
};


class AstPrinter : public Visitor<std::string> {
public:
    std::string visitAssignExpr(Assign<std::any> assign) {
        return std::string("");
    }
    std::string visitBinaryExpr(Binary<std::any> binary) {
        return std::string("");
    }
    std::string visitCallExpr(Call<std::any> call) {
        return std::string("");
    }
    std::string visitGetExpr(Get<std::any> get) {
        return std::string("");
    }
    std::string visitSetExpr(Set<std::any> set) {
        return std::string("");
    }
};




#endif //JLOX_VISITOR_H
