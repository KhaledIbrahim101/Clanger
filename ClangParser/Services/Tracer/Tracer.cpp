#include "Tracer.hpp"
#include "CallExprSt.hpp"
#include "CompoundSt.hpp"
#include "BinaryOperatorSt.hpp"
#include "DoSt.hpp"
#include "WhileSt.hpp"
#include "ForSt.hpp"
#include "IfSt.hpp"
#include "SwitchSt.hpp"
#include "CodeFile.hpp"
extern CodeFile* CF;
extern set<CodeFile> CodeDB ;
Tracer::Tracer(void)
{
}


Tracer::~Tracer(void)
{
}

Function* Tracer::getFunctionToTrace(CodeTrace* cs)
{
    bool found = false;
    Function* tfun = nullptr;
    for(auto comp : CodeDB)
    {
        if(cs->getFileName().find(StringUtility::remove_extension(comp.getName())) != string::npos)
        {
            for(auto fun : comp.getGlobalFunctions())
            {
                if(cs->getFunctionName() == fun->getName())
                {
                    tfun = fun;
                    found = false;
                    break;
                }
            }
            if(found)
                break;
        }
    }
    if(!found)
    {
        for(auto comp : CodeDB)
        {
            for(auto fun : comp.getGlobalFunctions())
            {
                if(cs->getFunctionName() == fun->getName())
                {
                    found = true;
                    tfun = fun;
                    break;
                }
            }
            if(found)
                break;
        }
    }
    return tfun;
}

void Tracer::TraceStatement(CodeTrace* current,Statement* st,Variable* tvar)
{
    string type = st->getType();
    switch(StringUtility::str2int(type.c_str()))
    {
        case StringUtility::str2int("Compound"):
        {
            CompoundSt* compst = (CompoundSt*)st;
            list<Statement*> chsts = compst->getStatements();
            for(auto chst : chsts)
            {
                TraceStatement(current,chst);
            }
            break;
        }

        case StringUtility::str2int("Binary Operator"):
        {
            BinaryOperatorSt* binst = (BinaryOperatorSt*)st;
            current->CodeBlock.push_back(binst);
            if(tvar == nullptr)
            {
                TraceStatement(current,binst->getLeftSide(),tvar);
                TraceStatement(current,binst->getRightSide(),tvar);
            }
            else
            {
                TraceStatement(current,binst->getRightSide());
            }
            break;
        }

        case StringUtility::str2int("Call Expression"):
        {
            CallExprSt* callst = (CallExprSt*)st;
            current->CodeBlock.push_back(callst);
            for(auto arg : callst->getArguments())
            {
                TraceStatement(current,arg);
            }
            CodeTrace* cs = new CodeTrace();
            cs->setName("Trace_" + callst->getFunctionName() + "." + callst->getFuncDeclFile());
            cs->setFunctionName(callst->getFunctionName());
            cs->setFileName(callst->getFuncDeclFile());            
            TraceFunction(cs);
            current->CodeBranches.push_back(cs);
            break;
        }

        case StringUtility::str2int("Do"):
        {
            DoSt* dost = (DoSt*)st;
            current->CodeBlock.push_back(new Statement("Do Start","Label"));
            list<Statement*> chsts = dost->getStatements();
            for(auto chst : chsts)
            {
                TraceStatement(current,chst);
            }
            TraceStatement(current,dost->getConditionStatement());
            current->CodeBlock.push_back(new Statement("Do End","Label"));
            break;
        }

        case StringUtility::str2int("While"):
        {
            WhileSt* whilest = (WhileSt*)st;
            TraceStatement(current,whilest->getConditionStatement());
            current->CodeBlock.push_back(new Statement("While Start","Label"));
            list<Statement*> chsts = whilest->getStatements();
            for(auto chst : chsts)
            {
                TraceStatement(current,chst);
            }
            current->CodeBlock.push_back(new Statement("While End","Label"));
            break;
        }

        case StringUtility::str2int("For"):
        {
            ForSt* forst = (ForSt*)st;
            TraceStatement(current,forst->getInitStatement());
            TraceStatement(current,forst->getConditionStatement());
            current->CodeBlock.push_back(new Statement("For Start","Label"));
            list<Statement*> chsts = forst->getStatements();
            for(auto chst : chsts)
            {
                TraceStatement(current,chst);
            }
            TraceStatement(current,forst->getIncrementStatement());
            current->CodeBlock.push_back(new Statement("For End","Label"));
            break;
        }

        case StringUtility::str2int("If else"):
        {
            IfSt* ifSt = (IfSt*)st;
            //TraceStatement(current,ifSt->getCondition());
            current->CodeBlock.push_back(new Statement("If(" + ifSt->getCondition()->getText() + ")" ,"Label"));
            list<Statement*> chsts = ifSt->getThenStatements();
            for(auto chst : chsts)
            {
                TraceStatement(current,chst);
            }
            current->CodeBlock.push_back(new Statement("If End","Label"));
            chsts = ifSt->getElseStatements();
            current->CodeBlock.push_back(new Statement("Else Start","Label"));
            for(auto chst : chsts)
            {
                TraceStatement(current,chst);
            }
            current->CodeBlock.push_back(new Statement("Else End","Label"));
            break;
        }

        case StringUtility::str2int("Switch"):
        {
            SwitchSt* switchst = (SwitchSt*)st;
            current->CodeBlock.push_back(new Statement("Switch Start","Label"));
            list<list<Statement*>> switchcases = switchst->getSwitchCases();
            for(auto scase : switchcases)
            {
                current->CodeBlock.push_back(new Statement("Case Start","Label"));
                for(auto casest : scase)
                {
                    TraceStatement(current,casest);
                }
                current->CodeBlock.push_back(new Statement("Case End","Label"));
            }
            current->CodeBlock.push_back(new Statement("Switch End","Label"));
            break;
        }

        default:
        {
            current->CodeBlock.push_back(st);
            break;
        }
    }
}

void Tracer::TraceVariable(CodeTrace* current,Variable* tvar)
{
    
}

void Tracer::TraceFunction(CodeTrace* current)
{
    Function* traceFuntion = getFunctionToTrace(current);
    if(traceFuntion != nullptr)
    {
        list<Statement*> statements = traceFuntion->getStatements();
        for(auto st : statements)
        {
            TraceStatement(current,st);
        }
    }
}