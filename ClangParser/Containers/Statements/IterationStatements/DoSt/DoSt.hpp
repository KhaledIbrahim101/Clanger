#ifndef DOST_H
#define DOST_H
#include <list>
#include <string>
#ifndef  STATEMENT_H  
#include "Statement.hpp"
#endif
using namespace std;
class DoSt : public Statement
{
	private:
		Statement* ConditionStatement;
		list<Statement*> Statements;
	public:
		DoSt();
		~DoSt();
		Statement* getConditionStatement();
		void setConditionStatement(Statement* ConditionStatement);
		void AddStatement(Statement* st);
		list<Statement*> getStatements();
		string ToString(string format) override;
		void FromString(string format,string buffer) override;
};
#endif