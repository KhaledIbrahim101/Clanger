#include "ForSt.hpp"  
#include "StatementHandler.hpp"
ForSt::ForSt()
{
	this->InitStatement = new Statement();
	this->InitStatement->setText("empty");
	this->ConditionStatement = new Statement();
	this->ConditionStatement->setText("empty");
	this->IncrementStatement = new Statement();
	this->IncrementStatement->setText("empty");
}

ForSt::~ForSt()
{
	
}

void ForSt::AddStatement(Statement* st)
{
    this->Statements.push_back(st);
}

Statement* ForSt::getIncrementStatement() 
{
	return this->IncrementStatement;
}
void ForSt::setIncrementStatement(Statement* IncrementStatement) 
{
	this->IncrementStatement = IncrementStatement;
}

Statement* ForSt::getConditionStatement() 
{
	return this->ConditionStatement;
}
void ForSt::setConditionStatement(Statement* ConditionStatement) 
{
	this->ConditionStatement = ConditionStatement;
}

Statement* ForSt::getInitStatement() 
{
	return this->InitStatement;
}
void ForSt::setInitStatement(Statement* InitStatement) 
{
	this->InitStatement = InitStatement;
}

list<Statement*> ForSt::getStatements()
{
	return this->Statements;
}

string ForSt::ToString(string format) 
{
	string buffer = "";

	if(format == "Json")
	{
		pt::ptree root, temp , array;
		root.put("Type", this->getType());
		temp = JsonUtility::GetJsonObject(this->InitStatement->ToString("Json"));
		root.put_child("Initialization",temp);
		temp = JsonUtility::GetJsonObject(this->ConditionStatement->ToString("Json"));
		root.put_child("Condition",temp);
		temp = JsonUtility::GetJsonObject(this->IncrementStatement->ToString("Json"));
		root.put_child("Increment",temp);
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
		string init = "", cond = "", inc = "";
		if(this->InitStatement != nullptr)
			init = this->InitStatement->getText();
		if(this->ConditionStatement != nullptr)
			cond = this->ConditionStatement->getText();
		if(this->IncrementStatement != nullptr)
			inc = this->IncrementStatement->getText();
		buffer = "[For Loop] for(" + init + " ; " + cond + " ; " + inc + ")\n" ;
		for (auto elem : this->Statements)
		{
			if(elem != nullptr)
				buffer += "\t" + elem->ToString("");
		}
	}
	
	return buffer;
}

void ForSt::FromString(string format,string buffer)
{
	if(format=="Json")
	{
		pt::ptree root = JsonUtility::GetJsonObject(buffer);
		//this->setText(root.get<string>("Text", "Undefined Text"));
		this->setType(root.get<string>("Type", "Undefined Type"));
		pt::ptree temp = root.get_child("Initialization");
		if(!temp.empty())
		{
			this->setInitStatement(StatementHandler::ReadJsonStatement(temp));
		}
		temp = root.get_child("Condition");
		if(!temp.empty())
		{
			this->setConditionStatement(StatementHandler::ReadJsonStatement(temp));
		}
		temp = root.get_child("Increment");
		if(!temp.empty())
		{
			this->setIncrementStatement(StatementHandler::ReadJsonStatement(temp));
		}
		for (pt::ptree::value_type &st : root.get_child("Statements"))
		{
			this->AddStatement(StatementHandler::ReadJsonStatement(st.second));
		}
	}
}