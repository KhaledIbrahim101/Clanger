#include "VarDeclHandler.hpp"
extern CodeFile* CF;
void VarDeclHandler::run(const MatchFinder::MatchResult &Result) 
{
    Variable* variable = new Variable();
    SourceManager &srcMgr = Result.Context->getSourceManager();
    if(const VarDecl* var = Result.Nodes.getNodeAs<VarDecl>("declaration")) 
    {
        variable->setName(var->getName().str());
        variable->setTypeName(var->getType().getAsString());
        if(var->isFunctionOrMethodVarDecl()) 
        {
            //string funName = ((CXXMethodDecl*)(var->getParentFunctionOrMethod()))->getQualifiedNameAsString();
            //llvm::outs() << "--" << srcMgr.getFilename(var->getLocation()).str();
        }
        if(var->hasExternalStorage()) 
        {
            CF->AddExternVariable(*variable);
            //llvm::outs() << "--" << srcMgr.getFilename(var->getLocation()).str();
        }
        else if(var->hasGlobalStorage()) 
        {
            CF->AddGlobalVariable(*variable);
            //llvm::outs() << "--" << srcMgr.getFilename(var->getLocation()).str();
        }
    }
}
