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
		bool isVirtual;
		string AccessModifer;
		Variable ReturnVarible;
		set<Variable> Parameters = {};
		list<Statement*> Statements = {};

	public:
		Function();
		~Function();
		string getName();
		void setName(string Name);
		bool getisVirtual();
		void setisVirtual(bool isVir);
    	Variable getReturnVarible();
    	void setReturnVarible(Variable ReturnVarible);
		string getAccessModifer();
		void setAccessModifer(string AccessModifer);
    	void AddParameter(Variable param);
		void AddStatement(Statement* statement);
		list<Statement*> getStatements();
		string ToString(string format);
		void FromString(string format, string buffer);
		bool operator< (const Function & msgObj) const;
};
#endif