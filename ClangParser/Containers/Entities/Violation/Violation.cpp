#include "Violation.hpp"  

Violation::Violation()
{

}

Violation::~Violation()
{

}

string Violation::getStandardName()
{
    return this->StandardName;
}

void Violation::setStandardName(string StandardName)
{
    this->StandardName = StandardName;
}

string Violation::getRuleName()
{
    return this->RuleName;
}

void Violation::setRuleName(string RuleName)
{
    this->RuleName = RuleName;
}

string Violation::getRuleDescription() 
{
    return this->RuleDescription;
}
void Violation::setRuleDescription(string RuleDescription) 
{
    this->RuleDescription = RuleDescription;
}

string Violation::getAction() 
{
	return this->Action;
}

void Violation::setAction(string Action) 
{
	this->Action = Action;
}

bool Violation::operator< (const Violation & msgObj) const
{
	std::string rightStr =  msgObj.StandardName + " " + msgObj.RuleName ;
	std::string leftStr = 	this->StandardName + this->RuleName ;
	return (leftStr < rightStr);
}

string Violation::ToString(string format)
{
	string buffer = "";
    if(format=="Json")
    {
        pt::ptree root, temp , array;
		root.put("Standard Name", StandardName);
        root.put("Rule Name", RuleName);
        root.put("Rule Description", RuleDescription);
        root.put("Action", Action);
		buffer = JsonUtility::GetJsonString(root);
    }
    else
    {

    }
	return buffer;
}

void Violation::FromString(string format, string buffer)
{
    if(format=="Json")
    {
        pt::ptree root = JsonUtility::GetJsonObject(buffer);
        this->setStandardName("");
        this->setRuleName("");
        this->setRuleDescription("");
        this->setAction("");
    }
}