#include "Statement.hpp"  
#include <algorithm>
using namespace std;

Statement::Statement()
{
	Text = "";
	Type = "Unhandled";	
}

Statement::Statement(string text, string type)
{
	Text = text;
	Type = type;	
}

Statement::~Statement()
{

}

string Statement::getText() 
{
	return this->Text;
}
void Statement::setText(string text) 
{
	this->Text = text;
}

string Statement::getType() 
{
	return this->Type;
}
void Statement::setType(string type) 
{
	this->Type = type;
}

pt::ptree Statement::GetInitialpTree()
{
	pt::ptree root;
	string textval = Text;
	replace(textval.begin(),textval.end(),'\"','\'');
	root.put("Text", JsonUtility::escape_json(textval));
	return root;
}

string Statement::ToString(string format)  
{
	string buffer = "";

	if(format == "Json")
	{
		pt::ptree root = GetInitialpTree();
		root.put("Type", this->getType());
		buffer = JsonUtility::GetJsonString(root);
	}
	else
	{
		buffer = "[Statement] " + this->Text ;
	}
	
	return buffer;
}

void Statement::FromString(string format, string buffer)  
{
	if(format=="Json")
	{
		pt::ptree root = JsonUtility::GetJsonObject(buffer);
		this->setText(root.get<string>("Text", "Undefined Text"));
		this->setType(root.get<string>("Type", "Undefined Type"));
	}
}
	