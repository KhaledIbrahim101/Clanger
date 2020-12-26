#include "Function.hpp"
#include "StatementHandler.hpp" 
#include <algorithm>
#include <functional> 
using namespace std;
Function::Function()
{
	Statements = {};
}

Function::~Function()
{
    
}

string Function::getName()
{
    return this->Name;
}

void Function::setName(string Name)
{
    this->Name = Name;
}

Variable Function::getReturnVarible()
{
    return this->ReturnVarible;
}

void Function::setReturnVarible(Variable ReturnVarible)
{
    this->ReturnVarible = ReturnVarible;
}
void Function::AddParameter(Variable param)
{
    this->Parameters.insert(param);
}
void Function::AddStatement(Statement* statement)
{
    this->Statements.push_back(statement);
}
bool Function::operator< (const Function & msgObj) const
{
    if(msgObj.ReturnVarible < this->ReturnVarible)
    {
        return false;
    }
    else
	{
        string rightStr =  msgObj.Name ;
	    string leftStr = 	this->Name ;
	    return (leftStr < rightStr);
    }
}

string Function::ToString(string format)
{
	string buffer = "";
	if(format == "Json")
	{
		pt::ptree root, temp , array;
		root.put("Name", this->Name);
		root.put_child("Return", JsonUtility::GetJsonObject(this->ReturnVarible.ToString("Json")));
		for (auto elem : this->Parameters)
		{
			temp = JsonUtility::GetJsonObject(elem.ToString("Json"));
			pair<string,pt::ptree> pptree("Parameter",temp);
			array.push_back(pptree);
		}
		root.put_child("Parameters", array);
		array.clear();

		for (auto elem : this->Statements)
		{
			temp = JsonUtility::GetJsonObject(elem->ToString("Json"));
			array.push_back(std::make_pair("", temp));
			/*temp = JsonUtility::GetJsonObject(elem->ToString("Json"));
			pair<string,pt::ptree> pptree("Statement",temp);
			array.push_back(pptree);*/
		}
		root.put_child("Statements", array);
		buffer = JsonUtility::GetJsonString(root);
	}
	else
	{
		buffer = "Name: " +  Name + " , Return Type: " + ReturnVarible.getTypeName() + "\n" ;
		for (auto elem : this->Parameters)
		{
			buffer += "\t" + elem.ToString("") + "\n";
		}
		buffer += "Body:\n"; 
		for (auto elem : this->Statements)
		{
			buffer += "\t" + elem->ToString("") + "\n";
		}
	}
	return buffer;
}

void Function::FromString(string format,string buffer)
{
	if(format == "Json")
	{
		pt::ptree root = JsonUtility::GetJsonObject(buffer);
		this->setName(root.get<string>("Name", "Undefined Name"));
		pt::ptree temp = root.get_child("Return");
		if(!temp.empty())
		{
			Variable var;
			var.FromString("Json",JsonUtility::GetJsonString(temp));
			this->setReturnVarible(var);
		}
		for (pt::ptree::value_type &st : root.get_child("Statements"))
		{
			this->AddStatement(StatementHandler::ReadJsonStatement(st.second));
		}
		for (pt::ptree::value_type &st : root.get_child("Parameters"))
		{
			Variable var;
			var.FromString("Json",JsonUtility::GetJsonString(st.second));
			this->AddParameter(var);
		}
	}
}

list<Statement*> Function::getStatements()
{
    return Statements;
}