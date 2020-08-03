#include "BreakSt.hpp"  

BreakSt::BreakSt()
{

}

BreakSt::~BreakSt()
{

}

string BreakSt::getBreakText() 
{
	return this->BreakText;
}
void BreakSt::setBreakText(string BreakText) 
{
	this->BreakText = BreakText;
}

string BreakSt::ToString(string format) 
{
	string buffer = "";
	if(format == "Json")
	{
		pt::ptree root;
		string textval = this->getText();
		replace(textval.begin(),textval.end(),'\"','\'');
		root.put("Type", this->getType());
		root.put("Text", JsonUtility::escape_json(textval));
		buffer = JsonUtility::GetJsonString(root);
	}
	else
	{
		buffer = "[Break] " + this->BreakText + ";\n";
	}
	return buffer;
}

void BreakSt::FromString(string format, string buffer)  
{
	if(format=="Json")
	{
		pt::ptree root = JsonUtility::GetJsonObject(buffer);
		this->setType(root.get<string>("Type", "Undefined Type"));
		this->setText(root.get<string>("Text", "Undefined Text"));
		this->setBreakText(root.get<string>("Text", "Undefined Text"));
	}
}