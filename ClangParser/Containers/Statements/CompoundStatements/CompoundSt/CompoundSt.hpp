#ifndef   COMPOUNDST_H
#define   COMPOUNDST_H
#include <list>
#include <string>
#ifndef  STATEMENT_H  
#include "Statement.hpp"
#endif
using namespace std;
class CompoundSt : public Statement
{
	private:
		list<Statement*> Statements;
	public:
		CompoundSt();
		~CompoundSt();
		void AddStatement(Statement* st);
		list<Statement*> getStatements();
		string ToString(string format) override;
		void FromString(string format, string buffer) override;
};
#endif