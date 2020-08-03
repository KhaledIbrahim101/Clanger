#include "CodeFile.hpp"  
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>
#ifndef  STATEMENTHANDLER_H  
#include <StatementHandler.hpp>
#endif
CodeFile::CodeFile()
{

}

CodeFile::~CodeFile()
{

}

string CodeFile::getName() 
{
	return this->Name;
}
void CodeFile::setName(string Name) 
{
	this->Name = Name;
}

string CodeFile::getPath() 
{
	return this->Path;
}
void CodeFile::setPath(string Path) 
{
	this->Path = Path;
}
bool CodeFile::operator< (const CodeFile & msgObj) const
{
	std::string rightStr = 	msgObj.Path ;
	std::string leftStr = 	this->Path ;
	return (leftStr < rightStr);
}

void CodeFile::AddGlobalVariable(Variable gvar)
{
    this->GlobalVariables.insert(gvar);
}

void CodeFile::AddExternVariable(Variable evar)
{
    this->ExternVariables.insert(evar);
}

void CodeFile::AddGlobalFunction(Function* gfun)
{
    this->GlobalFunctions.insert(gfun);
}

void CodeFile::AddInclude(IncludeSt* inc)
{
    this->Includes.insert(inc);
}

void CodeFile::AddViolation(Violation vio)
{
    this->Violations.insert(vio);
}

set<Function*> CodeFile::getGlobalFunctions()
{
	return this->GlobalFunctions;
}

string CodeFile::ToString(string format)
{
	string buffer = "";
	if(format == "Json")
	{
		pt::ptree root, temp , array;
		root.put("Name", Name);
		string pathval = Path;
		replace(pathval.begin(),pathval.end(),'\\','/');
		root.put("Path", pathval);
		
		for (auto elem : this->GlobalFunctions)
		{
			temp = JsonUtility::GetJsonObject(elem->ToString("Json"));
			pair<string,pt::ptree> pptree("Function",temp);
			array.push_back(pptree);
		}
		root.put_child("Functions", array);
		array.clear();

		for (auto elem : this->GlobalVariables)
		{
			temp = JsonUtility::GetJsonObject(elem.ToString("Json"));
			pair<string,pt::ptree> pptree("Global Variable",temp);
			array.push_back(pptree);
		}
		root.put_child("Global Variables", array);
		array.clear();

		for (auto elem : this->ExternVariables)
		{
			temp = JsonUtility::GetJsonObject(elem.ToString("Json"));
			pair<string,pt::ptree> pptree("Extern Variable",temp);
			array.push_back(pptree);
		}
		root.put_child("External Variables", array);
		array.clear();

		for (auto elem : this->Includes)
		{
			temp = JsonUtility::GetJsonObject(elem->ToString("Json"));
			pair<string,pt::ptree> pptree("Include Header",temp);
			array.push_back(pptree);
		}
		root.put_child("Include Headers", array);
		array.clear();

		buffer = JsonUtility::GetJsonString(root);
	}
	else
	{
		buffer ="File Name: " + Name + "\n" +
				"File Path: " + Path + "\n" +
				"Function Number : " + to_string(GlobalFunctions.size()) + "\n";
		for (auto elem : this->ExternVariables)
		{
			buffer += "[External Variable] " + elem.ToString("") + "\n";
		}
		for (auto elem : this->GlobalVariables)
		{
			buffer += "[Global Variable] " + elem.ToString("") + "\n";
		}
		for (auto elem : this->GlobalFunctions)
		{
			buffer += "[Global Function] " + elem->ToString("") + "\n";
		}
		buffer += "---------------------------\n";
		buffer += "---------------------------\n";
	}
	
	return buffer;
}

void CodeFile::FromString(string format, string buffer)
{
	if(format == "Json")
	{
		pt::ptree root = JsonUtility::GetJsonObject(buffer);
		this->setName(root.get<string>("Name", "Undefined Name"));
		this->setPath(root.get<string>("Path", "Undefined Path"));
		
		for (pt::ptree::value_type &st : root.get_child("Include Headers"))
		{
			this->Includes.insert((IncludeSt*)StatementHandler::ReadJsonStatement(st.second));
		}

		for (pt::ptree::value_type &st : root.get_child("Global Variables"))
		{
			Variable var;
			var.FromString("Json",JsonUtility::GetJsonString(st.second));
			this->GlobalVariables.insert(var);
		}

		for (pt::ptree::value_type &st : root.get_child("External Variables"))
		{
			Variable var;
			var.FromString("Json",JsonUtility::GetJsonString(st.second));
			this->ExternVariables.insert(var);
		}

		for (pt::ptree::value_type &st : root.get_child("Functions"))
		{
			Function* fun = new Function();
			fun->FromString("Json",JsonUtility::GetJsonString(st.second));
			GlobalFunctions.insert(fun);
		}
	}
	else
	{
		/* code */
	}
}