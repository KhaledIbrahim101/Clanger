#include "IfSt.hpp"  
#include "StatementHandler.hpp"
IfSt::IfSt()
{

}

IfSt::~IfSt()
{

}

Statement* IfSt::getCondition()
{
    return this->Condition;
}

void IfSt::setCondition(Statement* condition)
{
    this->Condition = condition;
}

void IfSt::AddThenStatement(Statement* st)
{
    this->Then.push_back(st);
}
void IfSt::AddElseStatement(Statement* st)
{
    this->Else.push_back(st);
}

list<Statement*> IfSt::getThenStatements()
{
	return this->Then;
}

list<Statement*> IfSt::getElseStatements()
{
	return this->Else;
}

string IfSt::ToString(string format) 
{
    string buffer = "";
	if(format == "Json")
	{
		pt::ptree root, temp , array;
		root.put("Type", this->getType());
		temp = JsonUtility::GetJsonObject(this->Condition->ToString("Json"));
		root.put_child("Condition",temp);
		for (auto elem : this->Then)
		{
			temp = JsonUtility::GetJsonObject(elem->ToString("Json"));
			pair<string,pt::ptree> pptree("Statement",temp);
			array.push_back(pptree);
		}
		root.put_child("Then", array);
		array.clear();
		for (auto elem : this->Else)
		{
			temp = JsonUtility::GetJsonObject(elem->ToString("Json"));
			pair<string,pt::ptree> pptree("Statement",temp);
			array.push_back(pptree);
		}
		root.put_child("Else", array);
		buffer = JsonUtility::GetJsonString(root);
	}
	else
	{
        buffer = "[If Condition] " + this->getCondition()->getText() + "\n" ;
        buffer += "Then,\n";
        for (auto elem : this->Then)
        {
            buffer += "\t" + elem->ToString("") + "\n";
        }
        buffer += "Else,\n";
        for (auto elem : this->Else)
        {
            buffer += "\t" + elem->ToString("") + "\n";
        }
    }
    
	return buffer; 
}

void IfSt::FromString(string format, string buffer)
{
	if(format=="Json")
	{
		pt::ptree root = JsonUtility::GetJsonObject(buffer);
		//this->setText(root.get<string>("Text", "Undefined Text"));
		this->setType(root.get<string>("Type", "Undefined Type"));
		pt::ptree temp = root.get_child("Condition");
		if(!temp.empty())
		{
			this->setCondition(StatementHandler::ReadJsonStatement(temp));
		}
		for (pt::ptree::value_type &st : root.get_child("Then"))
		{
			this->AddThenStatement(StatementHandler::ReadJsonStatement(st.second));
		}
		for (pt::ptree::value_type &st : root.get_child("Else"))
		{
			this->AddElseStatement(StatementHandler::ReadJsonStatement(st.second));
		}
	}
	
}