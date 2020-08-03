#include "DeclSt.hpp"  

DeclSt::DeclSt()
{

}

DeclSt::~DeclSt()
{

}

string DeclSt::getEntity() 
{
	return this->Entity;
}
void DeclSt::setEntity(string Entity) 
{
	this->Entity = Entity;
}

string DeclSt::ToString(string format) 
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
		buffer = "[Declaration] " + this->Entity + "\n";
	}
	
	return buffer ;
}

void DeclSt::FromString(string format, string buffer)  
{
	if(format=="Json")
	{
		pt::ptree root = JsonUtility::GetJsonObject(buffer);
		this->setText(root.get<string>("Text", "Undefined Text"));
		this->setEntity(root.get<string>("Text", "Undefined Text"));
		this->setType(root.get<string>("Type", "Undefined Type"));
	}
}