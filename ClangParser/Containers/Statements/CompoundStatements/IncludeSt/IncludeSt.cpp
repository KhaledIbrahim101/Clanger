#include "IncludeSt.hpp"  

IncludeSt::IncludeSt()
{

}

IncludeSt::~IncludeSt()
{

}

string IncludeSt::getIncludeType()
{
	return IncludeType;
}

void IncludeSt::setIncludeType(string type)
{
	IncludeType = type;
}

void IncludeSt::setFileName(string name)
{
	FileName = name;
}

string IncludeSt::getFileName()
{
	return FileName;
}

bool IncludeSt::operator< (const IncludeSt & msgObj) const
{
	string left  = this->FileName;
	string right = msgObj.FileName;  
	return left < right ;
}

string IncludeSt::ToString(string format) 
{
	string buffer = "";
	if(format == "Json")
	{
		pt::ptree root = GetInitialpTree();
		root.put("Type", this->getType());
		root.put("Include Type", IncludeType);
		root.put("File Name", FileName);
		root.put("Text", JsonUtility::escape_json(getText()));
		buffer = JsonUtility::GetJsonString(root);
	}
	else
	{
		buffer = "[Include] " + this->getText() + "\n";
	}
	
	return buffer ;
}

void IncludeSt::FromString(string format, string buffer)  
{
	if(format=="Json")
	{
		pt::ptree root = JsonUtility::GetJsonObject(buffer);
		this->setText(root.get<string>("Text", "Undefined Text"));
		this->setType(root.get<string>("Type", "Undefined Type"));
		this->setFileName(root.get<string>("File Name", "Undefined File Name"));
		this->setIncludeType(root.get<string>("Include Type", "Undefined Include Type"));
	}
}