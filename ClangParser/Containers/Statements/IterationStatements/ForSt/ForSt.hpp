#ifndef FORST_H
#define FORST_H
#include <list>
#include <string>
#ifndef  STATEMENT_H  
#include "Statement.hpp"
#endif
using namespace std;
class ForSt : public Statement
{
	private:
		Statement* InitStatement;
		Statement* ConditionStatement;
		Statement* IncrementStatement;
		list<Statement*> Statements;
	public:
		ForSt();
		~ForSt();
		Statement* getInitStatement();
		void setInitStatement(Statement* InitStatement);
		Statement* getConditionStatement();
		void setConditionStatement(Statement* ConditionStatement);
		Statement* getIncrementStatement();
		void setIncrementStatement(Statement* IncrementStatement);
		void AddStatement(Statement* st);
		list<Statement*> getStatements();
		string ToString(string format) override;
		void FromString(string format,string buffer) override;
};
#endif