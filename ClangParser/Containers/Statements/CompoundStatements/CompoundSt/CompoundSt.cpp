#include "CompoundSt.hpp"  
#include "StatementHandler.hpp"
CompoundSt::CompoundSt()
{

}

CompoundSt::~CompoundSt()
{
	
}

void CompoundSt::AddStatement(Statement* st)
{
    this->Statements.push_back(st);
}

list<Statement*> CompoundSt::getStatements()
{
	return this->Statements;
}

string CompoundSt::ToString(string format) 
{
	string buffer = "";
	if(format == "Json")
	{
		pt::ptree root, temp , array;
		root.put("Type", this->getType());
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
		buffer = "[Compound]\n{" ;
		for (auto elem : this->Statements)
		{
			if(elem != nullptr)
				buffer += "\t" + elem->ToString("");
		}
		buffer += "}";
	}
	
	return buffer;
}

void CompoundSt::FromString(string format, string buffer)  
{
	if(format=="Json")
	{
		pt::ptree root = JsonUtility::GetJsonObject(buffer);
		//this->setText(root.get<string>("Text", "Undefined Text"));
		this->setType(root.get<string>("Type", "Undefined Type"));
		for (pt::ptree::value_type &st : root.get_child("Statements"))
		{
			this->AddStatement(StatementHandler::ReadJsonStatement(st.second));
		}
	}
}