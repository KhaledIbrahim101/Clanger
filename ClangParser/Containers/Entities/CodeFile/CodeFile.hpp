#ifndef   CODEFILE_H
#define   CODEFILE_H
#include <iostream>
#include <string>
#include <list>
#include <set> 
#include <iterator> 
#include <IncludeSt.hpp>
#include <Violation.hpp>
/*#ifndef  FUNCTION_H  
#include <Function.hpp>
#endif*/
#ifndef  CLASS_H  
#include <Class.hpp>
#endif

using namespace std;
class CodeFile  
{
	private:
		string Name;
		string Path;
		set<Variable> GlobalVariables;
		set<Variable> ExternVariables;
		set<Function*> GlobalFunctions;
		set<IncludeSt*> Includes;
		set<Class*> Classes;
		set<Violation> Violations;
	public:
		CodeFile();
		~CodeFile();
		string getName();
		void setName(string Name);
		string getPath();
		void setPath(string Path);
		void AddGlobalVariable(Variable gvar);
		void AddExternVariable(Variable evar);
		void AddGlobalFunction(Function* gfun);
		void AddInclude(IncludeSt* inc);
		void AddClass(Class* cls);
		void AddViolation(Violation vio);
		set<Function*> getGlobalFunctions();
		string ToString(string format);
		void FromString(string format, string buffer);
		bool operator< (const CodeFile & msgObj) const;
};
#endif