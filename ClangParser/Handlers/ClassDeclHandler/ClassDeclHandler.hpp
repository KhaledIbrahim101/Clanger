#include "clang/AST/AST.h"

#include "clang/Rewrite/Core/Rewriter.h"

#include <string>
#ifndef  CLASS_H  
#include "Class.hpp"
#endif
#ifndef  FUNCTIONHANDLER_H  
#include <FunctionDeclHandler.hpp>
#endif
#ifndef  CODEFILE_H  
#include <CodeFile.hpp>
#endif
using namespace clang;
using namespace clang::ast_matchers;
using namespace std;
class ClassDeclHandler : public MatchFinder::MatchCallback
{
  public:
    ClassDeclHandler(Rewriter &Rewrite) : Rewrite(Rewrite) {}
    virtual void run(const MatchFinder::MatchResult &Result);

  private:
    Rewriter &Rewrite;
};