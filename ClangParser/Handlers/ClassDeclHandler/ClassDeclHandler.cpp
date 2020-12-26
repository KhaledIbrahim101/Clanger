#include "ClassDeclHandler.hpp"
extern CodeFile* CF;
Class* currentClass;
void ClassDeclHandler::run(const MatchFinder::MatchResult &Result) 
{
    int paramsNumber = 0;
    currentClass = new Class();
    Variable variable;
    Statement statement;

    if (const CXXRecordDecl *classDecl = Result.Nodes.getNodeAs<clang::CXXRecordDecl>("CXXRecordDecl")) 
    {
        if(classDecl->hasDefinition())
        {
            string classname = classDecl->getNameAsString();
            currentClass->setName(classname);
            string bodyfile =  StringUtility::remove_extension(StringUtility::base_name(classDecl->getLocation().printToString(*(Result.SourceManager))));
            string currentfile = StringUtility::remove_extension(StringUtility::base_name(CF->getPath())); 
            for(auto field : classDecl->fields())
            {
                FieldDecl* fd = (FieldDecl*)field;
                Variable* v = new Variable();
                v->setName(fd->getNameAsString());
                v->setTypeName(fd->getQualifiedNameAsString());
                if(fd->isModulePrivate())
                {
                    currentClass->AddPrivateVariable(*v);
                }
                else
                {
                    currentClass->AddPublicVariable(*v);
                }
            }
            for(auto method : classDecl->methods())
            {
                CXXRecordDecl* md = (CXXRecordDecl*)method;
                if(md->isCXXClassMember())
                {
                    FunctionDecl *fundecl = md->getAsFunction();
                    Function* currentfunction = new Function();
                    currentfunction->setName(fundecl->getNameAsString());
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
                    currentfunction->AddStatement(StatementHandler::Handle(st));
                    /*for (auto fst = st->child_begin(); fst != st->child_end(); fst++)
                    {
                        Statement* ast = StatementHandler::Handle(*fst);
                        currentfunction->AddStatement(ast);
                    }*/
                    
                    if(md->isExternallyVisible())
                    {
                        currentClass->AddPublicFunction(currentfunction);
                    }
                    else if(md->isModulePrivate())
                    {
                        currentClass->AddPrivateFunction(currentfunction);
                    }
                }
            }
            CF->AddClass(currentClass);
        }
    }
}