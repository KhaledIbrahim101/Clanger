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


bool Class::operator< (const Class & msgObj) const
{
	std::string rightStr = 	msgObj.Name ;
	std::string leftStr = 	this->Name ;
	return (leftStr < rightStr);
}

void Class::AddPublicVariable(Variable gvar)
{
    this->PublicVariables.insert(gvar);
}

void Class::AddPrivateVariable(Variable gvar)
{
    this->PrivateVariables.insert(gvar);
}

void Class::AddPublicFunction(Function* gfun)
{
    this->PublicFunctions.insert(gfun);
}

void Class::AddPrivateFunction(Function* gfun)
{
    this->PrivateFunctions.insert(gfun);
}

set<Function*> Class::getPublicFunctions()
{
	return this->PublicFunctions;
}

string Class::ToString(string format)
{
	string buffer = "";
	if(format == "Json")
	{
		pt::ptree root, temp , array;
		root.put("Name", Name);
		
		for (auto elem : this->PublicFunctions)
		{
			temp = JsonUtility::GetJsonObject(elem->ToString("Json"));
			array.push_back(std::make_pair("", temp));
			/*temp = JsonUtility::GetJsonObject(elem->ToString("Json"));
			pair<string,pt::ptree> pptree("Function",temp);
			array.push_back(pptree);*/
		}
		root.put_child("Public Functions", array);
		array.clear();

		for (auto elem : this->PublicVariables)
		{
			temp = JsonUtility::GetJsonObject(elem.ToString("Json"));
			array.push_back(std::make_pair("", temp));
			/*temp = JsonUtility::GetJsonObject(elem.ToString("Json"));
			pair<string,pt::ptree> pptree("Global Variable",temp);
			array.push_back(pptree);*/
		}
		root.put_child("Public Variables", array);
		array.clear();

		for (auto elem : this->PrivateVariables)
		{
			temp = JsonUtility::GetJsonObject(elem.ToString("Json"));
			array.push_back(std::make_pair("", temp));
			/*temp = JsonUtility::GetJsonObject(elem.ToString("Json"));
			pair<string,pt::ptree> pptree("Extern Variable",temp);
			array.push_back(pptree);*/
		}
		root.put_child("Private Variables", array);
		array.clear();

		for (auto elem : this->PrivateFunctions)
		{
			temp = JsonUtility::GetJsonObject(elem->ToString("Json"));
			array.push_back(std::make_pair("", temp));
			/*temp = JsonUtility::GetJsonObject(elem->ToString("Json"));
			pair<string,pt::ptree> pptree("Function",temp);
			array.push_back(pptree);*/
		}
		root.put_child("Private Functions", array);
		array.clear();

		buffer = JsonUtility::GetJsonString(root);
	}
	else
	{
		buffer ="File Name: " + Name + "\n" +
				"Function Number : " + to_string(PublicFunctions.size()) + "\n";
		for (auto elem : this->PrivateFunctions)
		{
			buffer += "[Private Function] " + elem->ToString("") + "\n";
		}
		for (auto elem : this->PublicVariables)
		{
			buffer += "[Public Variable] " + elem.ToString("") + "\n";
		}
		for (auto elem : this->PrivateVariables)
		{
			buffer += "[Private Variable] " + elem.ToString("") + "\n";
		}
		for (auto elem : this->PublicFunctions)
		{
			buffer += "[Public Function] " + elem->ToString("") + "\n";
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

		for (pt::ptree::value_type &st : root.get_child("Public Variables"))
		{
			Variable var;
			var.FromString("Json",JsonUtility::GetJsonString(st.second));
			this->PublicVariables.insert(var);
		}

		for (pt::ptree::value_type &st : root.get_child("Private Variables"))
		{
			Variable var;
			var.FromString("Json",JsonUtility::GetJsonString(st.second));
			this->PrivateVariables.insert(var);
		}

		for (pt::ptree::value_type &st : root.get_child("Public Functions"))
		{
			Function* fun = new Function();
			fun->FromString("Json",JsonUtility::GetJsonString(st.second));
			PublicFunctions.insert(fun);
		}

		for (pt::ptree::value_type &st : root.get_child("Private Functions"))
		{
			Function* fun = new Function();
			fun->FromString("Json",JsonUtility::GetJsonString(st.second));
			PrivateFunctions.insert(fun);
		}
	}
	else
	{
		/* code */
	}
}