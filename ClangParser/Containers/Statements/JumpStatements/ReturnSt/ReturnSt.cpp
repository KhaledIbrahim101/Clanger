#include "ReturnSt.hpp"  

ReturnSt::ReturnSt()
{

}

ReturnSt::~ReturnSt()
{

}

string ReturnSt::getReturnText() 
{
	return this->ReturnText;
}
void ReturnSt::setReturnText(string ReturnText) 
{
	this->ReturnText = ReturnText;
}

string ReturnSt::ToString(string format) 
{
	string buffer = "";
	if(format == "Json")
	{
		pt::ptree root = GetInitialpTree();
		string textval = this->getText();
		replace(textval.begin(),textval.end(),'\"','\'');
		root.put("Type", this->getType());
		root.put("Text", JsonUtility::escape_json(textval));
		buffer = JsonUtility::GetJsonString(root);
	}
	else
	{
		buffer = "[Return] " + this->ReturnText + ";\n";
	}
	return buffer;
}

void ReturnSt::FromString(string format, string buffer)  
{
	if(format=="Json")
	{
		pt::ptree root = JsonUtility::GetJsonObject(buffer);
		this->setType(root.get<string>("Type", "Undefined Type"));
		this->setText(root.get<string>("Text", "Undefined Text"));
		this->setReturnText(root.get<string>("Text", "Undefined Text"));
	}
}