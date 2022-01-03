#include "clang/AST/AST.h"

#include "clang/Rewrite/Core/Rewriter.h"

#include <string>
#ifndef  FUNCTION_H  
#include <Function.hpp>
#endif
#ifndef  STATEMENTHANDLER_H  
#include <StatementHandler.hpp>
#endif
#ifndef  CODEFILE_H  
#include <CodeFile.hpp>
#endif


using namespace clang;
using namespace clang::ast_matchers;
using namespace std;
class FunctionDeclHandler : public MatchFinder::MatchCallback
{
  public:
    FunctionDeclHandler(Rewriter &Rewrite) : Rewrite(Rewrite) {}
    virtual void run(const MatchFinder::MatchResult &Result);
  private:
    Rewriter &Rewrite;
    
};