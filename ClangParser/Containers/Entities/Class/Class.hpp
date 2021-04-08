#ifndef   CLASS_H
#define   CLASS_H
#include <iostream>
#include <string>
#include <list>
#include <set> 
#include <iterator>
#ifndef  FUNCTION_H  
#include <Function.hpp>
#endif

using namespace std;
class Class  
{
	private:
		string Name;
		string AccessModifer;
		bool isVirtual;
		bool isFinal;
		set<Variable> Variables;
		set<Function*> Functions;
		set<string> Relations;
	public:
		Class();
		~Class();
		string getName();
		void setName(string Name);
		bool getisVirtual();
		void setisVirtual(bool isVir);
		bool getisFinal();
		void setisFinal(bool isFin);
		string getAccessModifer();
		void setAccessModifer(string AccessModifer);
		void AddVariable(Variable gvar);
		void AddFunction(Function* gfun);
		void AddRelation(string rel);
		set<Function*> getFunctions();
		string ToString(string format);
		void FromString(string format, string buffer);
		bool operator< (const Class & msgObj) const;
};
#endif