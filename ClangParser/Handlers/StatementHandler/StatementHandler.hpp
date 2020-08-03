#ifndef   STATEMENTHANDLER_H
#define   STATEMENTHANDLER_H
#include "clang/AST/AST.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/AST/ExternalASTSource.h"
#include "clang/Lex/Preprocessor.h"
#include "llvm/Support/Casting.h"
#include <string>
#include <Statement.hpp>
#include <iostream>
using namespace clang;
using namespace clang::ast_matchers;
using namespace std;

class StatementHandler
{
    public:
        static Statement* Handle(const Stmt* st); 
        static Statement* HandleDecl(const Stmt* st);
        static Statement* HandleBinaryOperator(const Stmt* st);
        static Statement* HandleIf(const Stmt* st);
        static Statement* HandleFor(const Stmt* st);
        static Statement* HandleDoWhile(const Stmt* st);
        static Statement* HandleWhile(const Stmt* st);
        static Statement* HandleCompound(const Stmt* st);
        static Statement* HandleSwitch(const Stmt* st);
        static Statement* HandleFunctionCall(const Stmt* st);
        static Statement* HandleReturn(const Stmt* st);
        static Statement* HandleBreak(const Stmt* st);
        static Statement* HandleOpaqueValueExpr(const Stmt* st);
        static Statement* ReadJsonStatement(pt::ptree root);
        static const MatchFinder::MatchResult *mResult;
    private:
        StatementHandler(){};
        ~StatementHandler(){};
};
#endif