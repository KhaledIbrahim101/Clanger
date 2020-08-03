#include "OpaqueValueExprSt.hpp"  

OpaqueValueExprSt::OpaqueValueExprSt()
{

}

OpaqueValueExprSt::~OpaqueValueExprSt()
{

}


string OpaqueValueExprSt::ToString(string format) 
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
		buffer = "[OpaqueValueExpr] ";
	}
	
	return buffer;
}

void OpaqueValueExprSt::FromString(string format,string buffer) 
{
	if(format=="Json")
	{
		pt::ptree root = JsonUtility::GetJsonObject(buffer);
		this->setText(root.get<string>("Text", "Undefined Text"));
		this->setType(root.get<string>("Type", "Undefined Type"));
	}
}