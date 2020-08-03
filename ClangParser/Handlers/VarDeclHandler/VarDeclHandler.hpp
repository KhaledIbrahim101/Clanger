#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/AST/ExternalASTSource.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <string>
#ifndef  CODEFILE_H  
#include <CodeFile.hpp>
#endif

using namespace clang;
using namespace clang::ast_matchers;
using namespace std;
class VarDeclHandler : public MatchFinder::MatchCallback 
{
  public:
    VarDeclHandler() {}
    virtual void run(const MatchFinder::MatchResult &Result);
};