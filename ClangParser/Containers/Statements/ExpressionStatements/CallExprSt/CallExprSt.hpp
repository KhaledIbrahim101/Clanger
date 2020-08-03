#ifndef CALLEXPRST_H
#define CALLEXPRST_H
#include <string>
#include <list>
#ifndef  STATEMENT_H  
#include "Statement.hpp"
#endif
using namespace std;
class CallExprSt : public Statement
{
	private:
		string FunctionName;
		string FuncDeclFile;
		list<Statement*> Arguments;
	public:
		CallExprSt();
		~CallExprSt();
		string getFunctionName();
		void setFunctionName(string FunctionName);
		string getFuncDeclFile();
		void setFuncDeclFile(string FuncDeclFile);
		string ToString(string format) override;
		void FromString(string format, string buffer) override;
		void AddArgument(Statement* st);
		list<Statement*> getArguments();
};
#endif