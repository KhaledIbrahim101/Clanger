#ifndef   FUNCTION_H
#define   FUNCTION_H
#include <iostream>
#include <string>
#include <list>
#include <set> 
#include <iterator> 
#include <Variable.hpp>
#include <Statement.hpp>
using namespace std;
class Function  
{
	private:
		string Name;
		Variable ReturnVarible;
		set<Variable> Parameters = {};
		list<Statement*> Statements = {};

	public:
		Function();
		~Function();
		string getName();
		void setName(string Name);
    	Variable getReturnVarible();
    	void setReturnVarible(Variable ReturnVarible);
    	void AddParameter(Variable param);
		void AddStatement(Statement* statement);
		list<Statement*> getStatements();
		string ToString(string format);
		void FromString(string format, string buffer);
		bool operator< (const Function & msgObj) const;
};
#endif