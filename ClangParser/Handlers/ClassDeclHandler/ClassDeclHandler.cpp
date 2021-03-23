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
        string bodyfile =  StringUtility::remove_extension(StringUtility::base_name(classDecl->getLocation().printToString(*(Result.SourceManager))));
        string currentfile = StringUtility::remove_extension(StringUtility::base_name(CF->getPath())); 
        if(classDecl->hasDefinition() && bodyfile == currentfile)
        {
            string classname = classDecl->getNameAsString();
            currentClass->setName(classname);
            //currentClass->setisVirtual(classDecl->virt)
            for(auto parent : classDecl->bases())
            {
                currentClass->AddRelation("Child of " + (string)parent.getType()->getAsRecordDecl()->getNameAsString());
            }

            for(auto field : classDecl->fields())
            {
                FieldDecl* fd = (FieldDecl*)field;
                const clang::QualType qt = fd->getType();
                const clang::Type* t = qt.getTypePtr();

                Variable* v = new Variable();
                v->setName(fd->getName());
                v->setTypeName(fd->getType().getAsString());
                if(!t->isBuiltinType() && v->getTypeName().find("class") != string::npos)
                {
                    currentClass->AddRelation("Compsition of " + v->getTypeName());
                }
                if(fd->getAccess() == AccessSpecifier::AS_private)
                {
                    v->setAccessModifer("Private");
                }
                else if(fd->getAccess() == AccessSpecifier::AS_public)
                {
                    v->setAccessModifer("Public");
                }
                else if(fd->getAccess() == AccessSpecifier::AS_protected)
                {
                    v->setAccessModifer("Protected");
                }
                currentClass->AddVariable(*v);
            }
            for(auto method : classDecl->methods())
            {
                CXXRecordDecl* md = (CXXRecordDecl*)method;
                if(md->isCXXClassMember())
                {
                    FunctionDecl *fundecl = md->getAsFunction();
                    Function* currentfunction = new Function();
                    currentfunction->setName(fundecl->getNameAsString());
                    //currentfunction->setisVirtual(md->is)
                    variable.setName("Return");
                    variable.setReferenceType("Return");
                    variable.setTypeName(fundecl->getReturnType().getAsString());
                    currentfunction->setReturnVarible(variable);
                    currentfunction->setisVirtual(fundecl->isVirtualAsWritten());
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

                    switch(fundecl->getAccess())
                    {
                        case AccessSpecifier::AS_private:
                            currentfunction->setAccessModifer("Private");
                            break;

                        case AccessSpecifier::AS_public:
                            currentfunction->setAccessModifer("Public");
                            break;

                        case AccessSpecifier::AS_protected:
                            currentfunction->setAccessModifer("Protected");
                            break;  
                        
                        default:

                            break;
                    }
                    
                    currentClass->AddFunction(currentfunction);
                }
            }
            CF->AddClass(currentClass);
        }
    }
}