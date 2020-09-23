#ifndef   TRACER_H
#define   TRACER_H
#include "CodeTrace.hpp"
#include <list>
#include <set> 

class Tracer
{
public:
	Tracer(void);
	~Tracer(void);
	static void TraceVariable(CodeTrace* current,Variable* tvar);
	static void TraceFunction(CodeTrace* current);
	static void TraceStatement(CodeTrace* current,Statement* st,Variable* tvar = nullptr);
	static Function* getFunctionToTrace(CodeTrace* cs);
};
#endif