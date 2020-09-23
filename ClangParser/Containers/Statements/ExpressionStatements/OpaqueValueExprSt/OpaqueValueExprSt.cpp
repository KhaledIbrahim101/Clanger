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
		pt::ptree root = GetInitialpTree();
		root.put("Type", this->getType());
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