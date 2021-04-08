#include "Class.hpp"  
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>
#ifndef  STATEMENTHANDLER_H  
#include <StatementHandler.hpp>
#endif
Class::Class()
{

}

Class::~Class()
{

}

string Class::getName() 
{
	return this->Name;
}
void Class::setName(string Name) 
{
	this->Name = Name;
}

string Class::getAccessModifer() 
{
	return this->AccessModifer;
}

void Class::setAccessModifer(string AccessModifer) 
{
	this->AccessModifer = AccessModifer;
}

bool Class::getisVirtual()
{
    return this->isVirtual;
}

void Class::setisFinal(bool isFin)
{
    this->isFinal = isFin;
}

bool Class::getisFinal()
{
    return this->isFinal;
}

void Class::setisVirtual(bool isVir)
{
    this->isVirtual = isVir;
}

bool Class::operator< (const Class & msgObj) const
{
	std::string rightStr = 	msgObj.Name ;
	std::string leftStr = 	this->Name ;
	return (leftStr < rightStr);
}

void Class::AddVariable(Variable gvar)
{
    this->Variables.insert(gvar);
}

void Class::AddFunction(Function* gfun)
{
    this->Functions.insert(gfun);
}

void Class::AddRelation(string rel)
{
    this->Relations.insert(rel);
}

set<Function*> Class::getFunctions()
{
	return this->Functions;
}

string Class::ToString(string format)
{
	string buffer = "";
	if(format == "Json")
	{
		pt::ptree root, temp , array;
		root.put("Name", Name);
		root.put("Access", this->AccessModifer);

		for (auto elem : this->Relations)
		{
			temp.put_value(elem);
			array.push_back(std::make_pair("", temp));
		}

		root.put_child("Relations", array);
		array.clear();

		for (auto elem : this->Functions)
		{
			temp = JsonUtility::GetJsonObject(elem->ToString("Json"));
			array.push_back(std::make_pair("", temp));
		}

		root.put_child("Functions", array);
		array.clear();

		for (auto elem : this->Variables)
		{
			temp = JsonUtility::GetJsonObject(elem.ToString("Json"));
			array.push_back(std::make_pair("", temp));
		}
		root.put_child("Variables", array);
		array.clear();

		buffer = JsonUtility::GetJsonString(root);
	}
	else
	{
		buffer ="File Name: " + Name + "\n" +
				"Function Number : " + to_string(Functions.size()) + "\n";
		for (auto elem : this->Functions)
		{
			buffer += "[Function] " + elem->ToString("") + "\n";
		}
		for (auto elem : this->Variables)
		{
			buffer += "[Variable] " + elem.ToString("") + "\n";
		}
		
		buffer += "---------------------------\n";
		buffer += "---------------------------\n";
	}
	
	return buffer;
}

void Class::FromString(string format, string buffer)
{
	if(format == "Json")
	{
		pt::ptree root = JsonUtility::GetJsonObject(buffer);
		this->setName(root.get<string>("Name", "Undefined Name"));
		this->setAccessModifer(root.get<string>("Access", "Undefined Access"));
		for (pt::ptree::value_type &st : root.get_child("Variables"))
		{
			Variable var;
			var.FromString("Json",JsonUtility::GetJsonString(st.second));
			this->Variables.insert(var);
		}

		for (pt::ptree::value_type &st : root.get_child("Functions"))
		{
			Function* fun = new Function();
			fun->FromString("Json",JsonUtility::GetJsonString(st.second));
			this->Functions.insert(fun);
		}
	}
	else
	{
		/* code */
	}
}