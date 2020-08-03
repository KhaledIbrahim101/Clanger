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

bool Tracer::getStageInfoByFunctionName(CodeStage* cs, string funname,string filename)
{
    bool found = false;
    for(auto comp : CodeDB)
    {
        if(filename.find(StringUtility::remove_extension(comp.getName())) != string::npos)
        {
            for(auto fun : comp.getGlobalFunctions())
            {
                if(funname == fun->getName())
                {
                    found = true;
                    cs->StageFile = comp;
                    cs->StageFunction = fun;
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
                if(funname == fun->getName())
                {
                    found = true;
                    cs->StageFile = comp;
                    cs->StageFunction = fun;
                    break;
                }
            }
            if(found)
                break;
        }
    }
    return found;
}

void Tracer::TraceStatement(CodeStage* current,Statement* st,Variable* tvar)
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
            CodeStage* cs = new CodeStage();
            bool exists = getStageInfoByFunctionName(cs,callst->getFunctionName(),callst->getFuncDeclFile());
            if(exists)
            {
                TraceFunction(cs);
            } 
            else
            {
                Variable V;
                V.setName("Return");
                V.setTypeName("Undefined Type");
                Function* fun = new Function();
                fun->setReturnVarible(V);
                fun->setName(callst->getFunctionName());
                for(auto elem : callst->getArguments())
                {
                    Variable param;
                    param.setName(elem->ToString("Json"));
                    param.setReferenceType("Parameter");
                    fun->AddParameter(param);
                }
                cs->StageFile.setName(callst->getFuncDeclFile());
                cs->StageFunction = fun;
            }
            current->Stages.push_back(cs);
            break;
        }

        case StringUtility::str2int("Do"):
        {
            DoSt* dost = (DoSt*)st;
            list<Statement*> chsts = dost->getStatements();
            for(auto chst : chsts)
            {
                TraceStatement(current,chst);
            }
            TraceStatement(current,dost->getConditionStatement());
            break;
        }

        case StringUtility::str2int("While"):
        {
            WhileSt* whilest = (WhileSt*)st;
            TraceStatement(current,whilest->getConditionStatement());
            list<Statement*> chsts = whilest->getStatements();
            for(auto chst : chsts)
            {
                TraceStatement(current,chst);
            }
            break;
        }

        case StringUtility::str2int("For"):
        {
            ForSt* forst = (ForSt*)st;
            TraceStatement(current,forst->getInitStatement());
            TraceStatement(current,forst->getConditionStatement());
            list<Statement*> chsts = forst->getStatements();
            for(auto chst : chsts)
            {
                TraceStatement(current,chst);
            }
            TraceStatement(current,forst->getIncrementStatement());
            break;
        }

        case StringUtility::str2int("If else"):
        {
            IfSt* ifSt = (IfSt*)st;
            TraceStatement(current,ifSt->getCondition());
            list<Statement*> chsts = ifSt->getThenStatements();
            for(auto chst : chsts)
            {
                TraceStatement(current,chst);
            }
            chsts = ifSt->getElseStatements();
            for(auto chst : chsts)
            {
                TraceStatement(current,chst);
            }
            break;
        }

        case StringUtility::str2int("Switch"):
        {
            SwitchSt* switchst = (SwitchSt*)st;
            list<list<Statement*>> switchcases = switchst->getSwitchCases();
            for(auto scase : switchcases)
            {
                for(auto casest : scase)
                {
                    TraceStatement(current,casest);
                }
            }
            break;
        }
    }
}

void Tracer::TraceVariable(CodeStage* current,Variable* tvar)
{
    
}

void Tracer::TraceFunction(CodeStage* current)
{
    list<Statement*> statements = current->StageFunction->getStatements();
    for(auto st : statements)
    {
        TraceStatement(current,st);
    }
}