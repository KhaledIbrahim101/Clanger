#ifndef IFST_H
#define IFST_H
#include <list>
#include <string>
#ifndef  STATEMENT_H  
#include "Statement.hpp"
#endif
using namespace std;

class IfSt : public Statement
{
	private:
		Statement* Condition;
		list<Statement*> Then;
		list<Statement*> Else;
	public:
		IfSt();
		~IfSt();
		Statement* getCondition();
		void setCondition(Statement* condition);
		void AddThenStatement(Statement* st);
		void AddElseStatement(Statement* st);
		list<Statement*> getThenStatements();
		list<Statement*> getElseStatements();
		string ToString(string format) override;
		void FromString(string format,string buffer) override;
};
#endif