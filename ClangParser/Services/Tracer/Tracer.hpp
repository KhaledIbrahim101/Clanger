#ifndef   TRACER_H
#define   TRACER_H
#include "CodeStage.hpp"
#include <list>
#include <set> 

class Tracer
{
public:
	Tracer(void);
	~Tracer(void);
	static void TraceVariable(CodeStage* current,Variable* tvar);
	static void TraceFunction(CodeStage* current);
	static void TraceStatement(CodeStage* current,Statement* st,Variable* tvar = nullptr);
	static bool getStageInfoByFunctionName(CodeStage* cs, string funname,string filename = "");
};
#endif