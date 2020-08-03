#include "DoSt.hpp"  
#include "StatementHandler.hpp"
DoSt::DoSt()
{

}

DoSt::~DoSt()
{
	
}

void DoSt::AddStatement(Statement* st)
{
    this->Statements.push_back(st);
}

Statement* DoSt::getConditionStatement() 
{
	return this->ConditionStatement;
}
void DoSt::setConditionStatement(Statement* ConditionStatement) 
{
	this->ConditionStatement = ConditionStatement;
}

list<Statement*> DoSt::getStatements()
{
	return this->Statements;
}

string DoSt::ToString(string format) 
{
	string buffer = "";

	if(format == "Json")
	{
		pt::ptree root, temp , array;
		root.put("Type", this->getType());
		temp = JsonUtility::GetJsonObject(this->ConditionStatement->ToString("Json"));
		root.put_child("Condition",temp);
		for (auto elem : this->Statements)
		{
			temp = JsonUtility::GetJsonObject(elem->ToString("Json"));
			pair<string,pt::ptree> pptree("Statement",temp);
			array.push_back(pptree);
		}
		root.put_child("Statements", array);
		buffer = JsonUtility::GetJsonString(root);
	}
	else
	{
		string cond = "";
		if(this->ConditionStatement != nullptr)
			cond = this->ConditionStatement->getText();
		buffer = "[Do Loop] for(" + cond +  ")\n" ;
		for (auto elem : this->Statements)
		{
			if(elem != nullptr)
				buffer += "\t" + elem->ToString("");
		}
	}
	
	return buffer;
}

void DoSt::FromString(string format,string buffer)
{
	if(format=="Json")
	{
		pt::ptree root = JsonUtility::GetJsonObject(buffer);
		this->setType(root.get<string>("Type", "Undefined Type"));
		pt::ptree temp = root.get_child("Condition");
		if(!temp.empty())
		{
			this->setConditionStatement(StatementHandler::ReadJsonStatement(temp));
		}
		for (pt::ptree::value_type &st : root.get_child("Statements"))
		{
			this->AddStatement(StatementHandler::ReadJsonStatement(st.second));
		}
	}
}