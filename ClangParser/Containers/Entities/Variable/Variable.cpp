#include "Variable.hpp"  

Variable::Variable()
{

}

Variable::~Variable()
{

}

string Variable::getName()
{
    return this->Name;
}

void Variable::setName(string Name)
{
    this->Name = Name;
}

string Variable::getTypeName()
{
    return this->TypeName;
}

void Variable::setTypeName(string TypeName)
{
    this->TypeName = TypeName;
}

size_t Variable::getTypeSize()
{
    return this->TypeSize;
}

void Variable::setTypeSize(size_t TypeSize)
{
    this->TypeSize = TypeSize;
}

string Variable::getInitValue() 
{
    return this->InitValue;
}
void Variable::setInitValue(string InitValue) 
{
    this->InitValue = InitValue;
}

string Variable::getReferenceType() 
{
	return this->ReferenceType;
}

void Variable::setReferenceType(string ReferenceType) 
{
	this->ReferenceType = ReferenceType;
}

string Variable::getAccessModifer() 
{
	return this->AccessModifer;
}

void Variable::setAccessModifer(string AccessModifer) 
{
	this->AccessModifer = AccessModifer;
}

bool Variable::operator< (const Variable & msgObj) const
{
	std::string rightStr =  to_string(msgObj.TypeSize) + msgObj.Name ;
	std::string leftStr = 	to_string(this->TypeSize) + this->Name ;
	return (leftStr < rightStr);
}

string Variable::ToString(string format)
{
	string buffer = "";
    if(format=="Json")
    {
		pt::ptree root, temp , array;
		root.put("Name", Name);
        root.put("Type", TypeName);
        root.put("Access", this->AccessModifer);
		buffer = JsonUtility::GetJsonString(root);
    }
    else
    {
	    buffer = "Ref Type: " + ReferenceType + " , Name: " +  Name + " , Type: " + TypeName ;
    }
	return buffer;
}

void Variable::FromString(string format, string buffer)
{
    if(format=="Json")
    {
        pt::ptree root = JsonUtility::GetJsonObject(buffer);
		this->setName(root.get<string>("Name", "Undefined Name"));
        this->setTypeName(root.get<string>("Type", "Undefined Type"));
    }
}