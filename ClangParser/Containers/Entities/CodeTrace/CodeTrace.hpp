#ifndef   CodeTrace_H
#define   CodeTrace_H
#include <iostream>
#include <string>
#include <CodeFile.hpp>
using namespace std;

class CodeTrace
{
private:
	string Name;
	string FileName;
	string FunctionName;
public:
	CodeTrace();
	~CodeTrace();
	list<Statement*> CodeBlock;
	list<CodeTrace*> CodeBranches;
	string getName();
	void setName(string Name);
	string getFileName();
	void setFileName(string FileName);
	string getFunctionName();
	void setFunctionName(string FunctionName);
	string ToString(string format);
	void FromString(string format, string buffer);
	bool operator< (const CodeTrace & msgObj) const;
};
#endif