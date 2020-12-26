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
		set<Variable> PublicVariables;
		set<Variable> PrivateVariables;
		set<Function*> PublicFunctions;
		set<Function*> PrivateFunctions;
	public:
		Class();
		~Class();
		string getName();
		void setName(string Name);
		void AddPublicVariable(Variable gvar);
		void AddPrivateVariable(Variable evar);
		void AddPublicFunction(Function* gfun);
		void AddPrivateFunction(Function* gfun);
		set<Function*> getPublicFunctions();
		string ToString(string format);
		void FromString(string format, string buffer);
		bool operator< (const Class & msgObj) const;
};
#endif