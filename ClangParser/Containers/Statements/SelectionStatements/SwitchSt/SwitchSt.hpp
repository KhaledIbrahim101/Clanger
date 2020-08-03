#ifndef SWITCHST_H
#define SWITCHST_H
#include <list>
#include <string>
#ifndef  STATEMENT_H  
#include "Statement.hpp"
#endif
using namespace std;

class SwitchSt : public Statement
{
	private:
		Statement* SwitchVariable;
		list<list<Statement*>> SwitchCases;
		list<Statement*> SwitchValues;
	public:
		SwitchSt();
		~SwitchSt();
		void setSwitchVariable(Statement* SV);
		Statement* getSwitchVariable();
		void AddSwitchValue(Statement* value);
		void AddSwitchCase(list<Statement*> casebody);
		list<list<Statement*>> getSwitchCases();
		string ToString(string format) override;
		void FromString(string format,string buffer) override;
};
#endif