#include "FunctionDeclHandler.hpp"
extern CodeFile* CF;
Function* currentfunction;
void FunctionDeclHandler::run(const MatchFinder::MatchResult &Result) 
{
    int paramsNumber = 0;
    currentfunction = new Function();
    Variable variable;
    Statement statement;

    if (const FunctionDecl *fundecl = Result.Nodes.getNodeAs<clang::FunctionDecl>("FunctionDecl")) 
    {
        string funname = fundecl->getNameAsString();
        string bodyfile =  StringUtility::remove_extension(StringUtility::base_name(fundecl->getLocation().printToString(*(Result.SourceManager))));
        string currentfile = StringUtility::remove_extension(StringUtility::base_name(CF->getPath())); 
        if(fundecl->hasBody() && bodyfile == currentfile)
        {//functions that are defined in the same files
            //llvm::outs()<< fundecl->getNameAsString()<<"\n"; // DONT REMOVE TO DISPLAY MAIN
            currentfunction->setName(funname);
            variable.setName("Return");
            variable.setReferenceType("Return");
            variable.setTypeName(fundecl->getReturnType().getAsString());
            currentfunction->setReturnVarible(variable);
            Variable Param;
            paramsNumber = fundecl->getNumParams();
            for(int iParam = 0 ; iParam < paramsNumber ; iParam++)
            {
                Param.setReferenceType("Parameter");
                Param.setName(fundecl->getParamDecl(iParam)->getNameAsString());
                Param.setTypeName(fundecl->getParamDecl(iParam)->getType().getAsString());
                currentfunction->AddParameter(Param);
            }
            Stmt *st = fundecl->getBody();
            StatementHandler::mResult = &Result;
            /*if(st->children().empty())
            {
                currentfunction->AddStatement(StatementHandler::Handle(st));
            }
            else
            {*/
                for (auto fst : st->children())
                {
                    Statement* ast = StatementHandler::Handle(fst);
                    currentfunction->AddStatement(ast);
                }
            //}
            
            CF->AddGlobalFunction(currentfunction);
        }  
        //else if(1==1)
        {//functions that are called but defined outside the file

        }
        //else if(1==0)
        {//functions that could be accessed but not called

        }
    }
    //delete(currentfunction);*/
}