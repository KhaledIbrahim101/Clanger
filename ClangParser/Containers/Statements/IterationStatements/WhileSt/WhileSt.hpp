#ifndef WHILEST_H
#define WHILEST_H
#include <list>
#include <string>
#ifndef  STATEMENT_H  
#include "Statement.hpp"
#endif
using namespace std;
class WhileSt : public Statement
{
	private:
		Statement* ConditionStatement;
		list<Statement*> Statements;
	public:
		WhileSt();
		~WhileSt();
		Statement* getConditionStatement();
		void setConditionStatement(Statement* ConditionStatement);
		void AddStatement(Statement* st);
		list<Statement*> getStatements();
		string ToString(string format) override;
		void FromString(string format,string buffer) override;
};
#endif