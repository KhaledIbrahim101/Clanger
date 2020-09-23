#include "CodeTrace.hpp"  
#include "StatementHandler.hpp"  
CodeTrace::CodeTrace()
{

}

CodeTrace::~CodeTrace()
{

}

string CodeTrace::getName() 
{
	return this->Name;
}
void CodeTrace::setName(string Name) 
{
	this->Name = Name;
}

string CodeTrace::getFileName() 
{
	return this->FileName;
}
void CodeTrace::setFileName(string FileName) 
{
	this->FileName = FileName;
}

string CodeTrace::getFunctionName() 
{
	return this->FunctionName;
}
void CodeTrace::setFunctionName(string FunctionName) 
{
	this->FunctionName = FunctionName;
}

bool CodeTrace::operator< (const CodeTrace & msgObj) const
{
	string rightStr =  msgObj.FileName + "." + msgObj.FunctionName;
	string leftStr = this->FileName + "." + this->FunctionName;
	return (leftStr < rightStr);
}

string CodeTrace::ToString(string format)
{
	string buffer = "";
    if(format=="Json")
    {
        pt::ptree root, temp , array;
        root.put("Name", this->Name);
        root.put("File", this->FileName);
        root.put("Function", this->FunctionName);
        for (auto elem : this->CodeBlock)
		{
			temp = JsonUtility::GetJsonObject(elem->ToString("Json"));
			array.push_back(std::make_pair("", temp));
		}
		root.add_child("Statements", array);   
        array.clear();
        for (auto elem : this->CodeBranches)
		{
			temp = JsonUtility::GetJsonObject(elem->ToString("Json"));
			array.push_back(std::make_pair("", temp));
		}
		root.add_child("Branches", array);   
        array.clear();
        buffer = JsonUtility::GetJsonString(root);
    }
    else
    {

    }
	return buffer;
}

void CodeTrace::FromString(string format, string buffer)
{
    if(format=="Json")
    {
        Function* fun = new Function();
        pt::ptree root = JsonUtility::GetJsonObject(buffer);
        this->setName(root.get<string>("Name", "Undefined Name"));
        this->setFileName(root.get<string>("File", "Undefined File"));
        this->setFunctionName(root.get<string>("Function", "Undefined Function"));
        
        for (pt::ptree::value_type &st : root.get_child("Block"))
		{
			this->CodeBlock.push_back(StatementHandler::ReadJsonStatement(st.second));
		}

        for (pt::ptree::value_type &st : root.get_child("Branches"))
		{
            CodeTrace* cs = new CodeTrace();
            cs->FromString("Json",JsonUtility::GetJsonString(st.second));
			this->CodeBranches.push_back(cs);
		}
    }
}