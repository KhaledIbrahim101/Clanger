#include "BinaryOperatorSt.hpp"  
#include "StatementHandler.hpp"
BinaryOperatorSt::BinaryOperatorSt()
{

}

BinaryOperatorSt::~BinaryOperatorSt()
{

}

Statement* BinaryOperatorSt::getLeftSide() 
{
	return this->LeftSide;
}
void BinaryOperatorSt::setLeftSide(Statement* LeftSide) 
{
	this->LeftSide = LeftSide;
}

Statement* BinaryOperatorSt::getRightSide() 
{
	return this->RightSide;
}
void BinaryOperatorSt::setRightSide(Statement* RightSide) 
{
	this->RightSide = RightSide;
}

string BinaryOperatorSt::getOpCode() 
{
	return this->OpCode;
}
void BinaryOperatorSt::setOpCode(string OpCode) 
{
	this->OpCode = OpCode;
}

string BinaryOperatorSt::ToString(string format) 
{
	string buffer = "";
	if(format == "Json")
	{
		pt::ptree root = GetInitialpTree(), temp;
		root.put("Type", this->getType());
		temp = JsonUtility::GetJsonObject( LeftSide->ToString("Json"));
		root.add_child("Left Side",temp);
		root.put("Operator", OpCode);
		temp = JsonUtility::GetJsonObject( RightSide->ToString("Json"));
		root.add_child("Right Side",temp);
		buffer = JsonUtility::GetJsonString(root);
	}
	else
	{
		buffer = "[Binary Operation] " + this->LeftSide->getText() + " " + this->OpCode + " " + this->RightSide->getText() + ";\n" + 
			"\t\t" + this->RightSide->ToString("");
	}

	return buffer;
}

void BinaryOperatorSt::FromString(string format, string buffer)  
{
	if(format=="Json")
	{
		pt::ptree root = JsonUtility::GetJsonObject(buffer);
		this->setText(root.get<string>("Text", "Undefined Text"));
		this->setType(root.get<string>("Type", "Undefined Type"));
		pt::ptree temp = root.get_child("Left Side");
		if(!temp.empty())
		{
			this->setLeftSide(StatementHandler::ReadJsonStatement(temp));
		}

		temp = root.get_child("Right Side");
		if(!temp.empty())
		{
			this->setRightSide(StatementHandler::ReadJsonStatement(temp));
		}

		this->setOpCode(root.get<string>("Operator", "Undefined Operator"));
	}
}
