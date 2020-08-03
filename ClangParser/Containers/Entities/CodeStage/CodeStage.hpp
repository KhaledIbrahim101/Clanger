#ifndef   CODESTAGE_H
#define   CODESTAGE_H
#include <iostream>
#include <string>
#include <CodeFile.hpp>
using namespace std;

class CodeStage
{
private:
	string Name;

public:
	CodeStage();
	~CodeStage();
	CodeFile StageFile;
	Function* StageFunction;
	list<CodeStage*> Stages;
	string getName();
	void setName(string Name);
	string ToString(string format);
	void FromString(string format, string buffer);
	bool operator< (const CodeStage & msgObj) const;
};
#endif