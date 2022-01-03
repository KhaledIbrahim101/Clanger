#include "StatementHandler.hpp"
#include <IncludeSt.hpp>
#include <IfSt.hpp>
#include <ForSt.hpp>
#include <DoSt.hpp>
#include <WhileSt.hpp>
#include <CompoundSt.hpp>
#include <SwitchSt.hpp>
#include <DeclSt.hpp>
//#include <CallExprSt.hpp> because needed in function decl handler and moved to hpp
#include <BinaryOperatorSt.hpp>
#include <OpaqueValueExprSt.hpp>  
#include <ReturnSt.hpp>
#include <BreakSt.hpp>

const MatchFinder::MatchResult* StatementHandler::mResult = NULL;

static string GetExprAsString(const Stmt* st)
{
    //Get the source manager.
    const SourceManager *SM = StatementHandler::mResult->SourceManager;
    //Use LLVM's lexer to get source text.
    string text = (string)Lexer::getSourceText(CharSourceRange::getTokenRange(st->getSourceRange()), *SM, LangOptions(), 0);
    if (text.size() > 0 && (text.at(text.size()-1) == ',')) //the text can be ""
        return (string)Lexer::getSourceText(CharSourceRange::getCharRange(st->getSourceRange()), *SM, LangOptions(), 0);
    return text;
}

Statement* StatementHandler::Handle(const Stmt* st)
{
    Statement* statement = new Statement();
    statement->setText("");
    if(st != nullptr)
    {
        switch(st->getStmtClass())
        {
            case clang::Stmt::StmtClass::DeclStmtClass:
                statement = new DeclSt();
                statement = HandleDecl(st);
                statement->setType("Declaration");
                break;

            case clang::Stmt::StmtClass::OpaqueValueExprClass:
                statement = new Statement();
                statement = HandleOpaqueValueExpr(st);
                statement->setType("Opaque Value Expression");
                break;
    
            case clang::Stmt::StmtClass::BinaryOperatorClass:
                statement = new BinaryOperatorSt();
                statement = HandleBinaryOperator(st);
                statement->setType("Binary Operator");
                break;

            case clang::Stmt::StmtClass::IfStmtClass:
                statement = new IfSt();
                statement = HandleIf(st);
                statement->setType("If else");
                break;

            case clang::Stmt::StmtClass::ReturnStmtClass:
                statement = new ReturnSt();
                statement = HandleReturn(st);
                statement->setType("Return");
                break;

            case clang::Stmt::StmtClass::BreakStmtClass:
                statement = new ReturnSt();
                statement = HandleBreak(st);
                statement->setType("Break");
                break;

            case clang::Stmt::StmtClass::CallExprClass:
                statement = new CallExprSt();
                statement = HandleFunctionCall(st);
                statement->setType("Call Expression");
                break;

            case clang::Stmt::StmtClass::SwitchStmtClass:
                statement = new SwitchSt();
                statement = HandleSwitch(st);
                statement->setType("Switch");
                break;
            
            case clang::Stmt::StmtClass::ForStmtClass:
                statement = new ForSt();
                statement = HandleFor(st);
                statement->setType("For");
                break;

            case clang::Stmt::StmtClass::DoStmtClass:
                statement = new Statement();
                statement = HandleDoWhile(st);
                statement->setType("Do");
                break;

            case clang::Stmt::StmtClass::WhileStmtClass:
                statement = new Statement();
                statement = HandleWhile(st);
                statement->setType("While");
                break;
            
            case clang::Stmt::StmtClass::CompoundStmtClass:
                statement = new Statement();
                statement = HandleCompound(st);
                statement->setType("Compound");
                break;

            case clang::Stmt::StmtClass::NullStmtClass:
            default:
                statement = new Statement();
                statement->setType("Null");
                break;
        }
        statement->setText(GetExprAsString(st) + "[" + st->getStmtClassName() + "]" );
    }
    if(statement->getText() == "")
    {
        statement->setText("empty");
        statement->setText("Not handled");
    }
    return statement;
}

Statement* StatementHandler::HandleBinaryOperator(const Stmt* st) 
{
    BinaryOperatorSt* sts = new BinaryOperatorSt();
    BinaryOperator* IfS = (BinaryOperator*)st;
    sts->setOpCode(IfS->getOpcodeStr().str());
    sts->setLeftSide(Handle(IfS->getLHS()));
    sts->setRightSide((Handle(IfS->getRHS())));
    return sts;
}

Statement* StatementHandler::HandleReturn(const Stmt* st) 
{
    ReturnSt* sts = new ReturnSt();
    ReturnStmt* IfS = (ReturnStmt*)st;
    if(IfS != nullptr)
        sts->setReturnText(GetExprAsString(st));
    return sts;
}

Statement* StatementHandler::HandleBreak(const Stmt* st) 
{
    BreakSt* sts = new BreakSt();
    BreakStmt* IfS = (BreakStmt*)st;
    if(IfS != nullptr)
        sts->setBreakText(GetExprAsString(st));
    return sts;
}

Statement* StatementHandler::HandleFunctionCall(const Stmt* st) 
{
    int argNumber = 0;
    CallExprSt* sts = new CallExprSt();
    CallExpr* IfS = (CallExpr*)st;
    FunctionDecl *func = IfS->getDirectCallee();
    if (func != NULL && IfS != NULL)
    {
        argNumber = IfS->getNumArgs();
        for(int i=0; i<argNumber; i++)
        {
            sts->AddArgument(Handle(IfS->getArg(i)));
        }
        sts->setFuncDeclFile(IfS->getCalleeDecl()->getLocation().printToString(*(mResult->SourceManager)));
        sts->setFunctionName(func->getQualifiedNameAsString());
    }
    return sts;
}

Statement* StatementHandler::HandleDecl(const Stmt* st) 
{
    DeclSt* sts = new DeclSt();
    DeclStmt* declSt = (DeclStmt*)st;
    sts->setEntity(GetExprAsString(declSt));
    return sts;
}

Statement* StatementHandler::HandleIf(const Stmt* st) 
{
    IfSt* sts = new IfSt();
    IfStmt* IfS = (IfStmt*)st;
    sts->setCondition(Handle(IfS->getCond()));
    const Stmt *Then = IfS->getThen();
    for (auto fst : Then->children())
    {
        sts->AddThenStatement(Handle(fst));
    }
    if(IfS->hasElseStorage())
    {
        if (const Stmt *Else = IfS->getElse()) 
        {
            for (auto est : Else->children())
            {
                sts->AddElseStatement(Handle(est));
            }
        }
    }
    
    return sts;
}

Statement* StatementHandler::HandleFor(const Stmt* st) 
{
    ForSt* sts = new ForSt();
    ForStmt* IfS = (ForStmt*)st;
    if(IfS->getInit() != nullptr)
        sts->setInitStatement(Handle(IfS->getInit()));
    if(IfS->getCond() != nullptr)
        sts->setConditionStatement(Handle(IfS->getCond()));
    if(IfS->getInc() != nullptr)
        sts->setIncrementStatement(Handle(IfS->getInc()));
    const Stmt *Then = IfS->getBody();
    for (auto fst : Then->children())
    {
        sts->AddStatement(Handle(fst));
    }
    return sts;
}

Statement* StatementHandler::HandleDoWhile(const Stmt* st) 
{
    DoSt* sts = new DoSt();
    DoStmt* IfS = (DoStmt*)st;
    if(IfS->getCond() != nullptr)
        sts->setConditionStatement(Handle(IfS->getCond()));
    const Stmt *Then = IfS->getBody();
    for (auto fst : Then->children())
    {
        sts->AddStatement(Handle(fst));
    }
    return sts;
}

Statement* StatementHandler::HandleWhile(const Stmt* st) 
{
    WhileSt* sts = new WhileSt();
    WhileStmt* IfS = (WhileStmt*)st;
    if(IfS->getCond() != nullptr)
        sts->setConditionStatement(Handle(IfS->getCond()));
    const Stmt *Then = IfS->getBody();
    for (auto fst : Then->children())
    {
        sts->AddStatement(Handle(fst));
    }
    return sts;
}

Statement* StatementHandler::HandleCompound(const Stmt* st) 
{
    CompoundSt* sts = new CompoundSt();
    CompoundStmt* IfS = (CompoundStmt*)st;
    for (auto fst : IfS->children())
    {
        sts->AddStatement(Handle(fst));
    }
    return sts;
}

Statement* StatementHandler::HandleSwitch(const Stmt* st) 
{
    list<Statement*> stBody;
    SwitchSt* sts = new SwitchSt();
    clang::SwitchStmt* IfS = (clang::SwitchStmt*)st;

    VarDecl* vd = IfS->getConditionVariable();
    if(vd != nullptr)
    {
        sts->setSwitchVariable(Handle(vd->getBody()));
    }
    else
    {
        DeclStmt* ds = IfS->getConditionVariableDeclStmt();
        if(ds != nullptr)
        {
            sts->setSwitchVariable(Handle(ds));
        }
    }
    bool newcase = false;
    Stmt* SCBody = (Stmt*)IfS->getBody();
    if(SCBody != NULL)
    {
        for (auto fst : SCBody->children())
        {
            string stringclass = fst->getStmtClassName();
            if(fst->getStmtClass() == clang::Stmt::StmtClass::CaseStmtClass ||
               fst->getStmtClass() == clang::Stmt::StmtClass::DefaultStmtClass)
            {
                if(newcase)
                {
                    sts->AddSwitchValue(stBody.front());
                    stBody.pop_front();
                    sts->AddSwitchCase(stBody);
                    stBody.clear();
                }
                newcase = true;
                for (auto cst : fst->children())
                {
                    stBody.push_back(Handle(cst));
                }
            }
            else if(fst->getStmtClass() == clang::Stmt::StmtClass::BreakStmtClass)
            {
                stBody.push_back(Handle(fst));
            }
            else
            {
                stBody.push_back(Handle(fst));
            }
        }
        sts->AddSwitchCase(stBody);
    }
    return sts;
}

Statement* StatementHandler::HandleOpaqueValueExpr(const Stmt* st) 
{
    OpaqueValueExprSt* sts = new OpaqueValueExprSt();
    clang::OpaqueValueExpr* IfS = (clang::OpaqueValueExpr*)st;
    sts->setText( GetExprAsString(IfS));
    return new Statement();
}

Statement* StatementHandler::ReadJsonStatement(pt::ptree root)
{
    string type = root.get<string>("Type", "Undefined Type");
    string j = JsonUtility::GetJsonString(root);
    Statement* statement;
    switch (StringUtility::str2int(type.c_str()))
    {
        case StringUtility::str2int("Compound"):
            CompoundSt* compst;
            compst = new CompoundSt();
            compst->FromString("Json",j);
            statement = compst;
            break;

        case StringUtility::str2int("Include"):
            IncludeSt* includest;
            includest = new IncludeSt();
            includest->FromString("Json",j);
            statement = includest;
            break;

        case StringUtility::str2int("Declaration"):
            DeclSt* declst;
            declst = new DeclSt();
            declst->FromString("Json",j);
            statement = declst;
            break;

        case StringUtility::str2int("Binary Operator"):
            BinaryOperatorSt* binst;
            binst = new BinaryOperatorSt();
            binst->FromString("Json",j);            
            statement = binst;
            break;
        
        case StringUtility::str2int("Call Expression"):
            CallExprSt* callexpr;
            callexpr = new CallExprSt();
            callexpr->FromString("Json",j);
            statement = callexpr;
            break;

        case StringUtility::str2int("Do"):
            DoSt* dost;
            dost = new DoSt();
            dost->FromString("Json",j);            
            statement = dost;
            break;

        case StringUtility::str2int("For"):
            ForSt* forst;
            forst = new ForSt();
            forst->FromString("Json",j);  
            statement = forst;
            break;

        case StringUtility::str2int("While"):
            WhileSt* whileset;
            whileset = new WhileSt();
            whileset->FromString("Json",j);
            statement = whileset;
            break;

        case StringUtility::str2int("Break"):
            BreakSt* breakSt;
            breakSt = new BreakSt();
            breakSt->FromString("Json",j);
            statement = breakSt;
            break;
        
        case StringUtility::str2int("Return"):
            ReturnSt* retst;
            retst = new ReturnSt();
            retst->FromString("Json",j);
            statement = retst;
            break;

        case StringUtility::str2int("If else"):
            IfSt* ifst;
            ifst = new IfSt();
            ifst->FromString("Json",j);
            statement = ifst;
            break;

        case StringUtility::str2int("Switch"):
            SwitchSt* switchst;
            switchst = new SwitchSt();
            switchst->FromString("Json",j);
            statement = switchst;
            break;

        case StringUtility::str2int("Opaque Value Expression"):
        case StringUtility::str2int("Unhandled"):
        default:
            statement = new Statement();
            statement->FromString("Json",j);
            break;

    }
    return statement;
}
