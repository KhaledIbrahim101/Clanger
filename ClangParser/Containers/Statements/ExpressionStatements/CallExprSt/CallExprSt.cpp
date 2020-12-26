#include "CallExprSt.hpp"  
#include "StatementHandler.hpp"
CallExprSt::CallExprSt()
{

}

CallExprSt::~CallExprSt()
{

}

string CallExprSt::getFunctionName() 
{
	return this->FunctionName;
}
void CallExprSt::setFunctionName(string FunctionName) 
{
	this->FunctionName = FunctionName;
}

string CallExprSt::getFuncDeclFile() 
{
	return this->FuncDeclFile;
}
void CallExprSt::setFuncDeclFile(string FuncDeclFile) 
{
	this->FuncDeclFile = FuncDeclFile;
}

list<Statement*> CallExprSt::getArguments()
{
	return this->Arguments;
}

string CallExprSt::ToString(string format) 
{
	string buffer = "";

	if(format == "Json")
	{
		pt::ptree root = GetInitialpTree(), temp, array;
		string pathval = FuncDeclFile;
		replace(pathval.begin(),pathval.end(),'\\','/');
		root.put("Type", this->getType());
		root.put("Definition File", pathval);
		root.put("Called Function", FunctionName);
		for (auto elem : this->Arguments)
		{
			temp = JsonUtility::GetJsonObject(elem->ToString("Json"));
			array.push_back(std::make_pair("", temp));
			/*temp = JsonUtility::GetJsonObject(elem->ToString("Json"));
			pair<string,pt::ptree> pptree("Argument",temp);
			array.push_back(pptree);*/
		}
		root.put_child("Arguments", array);
		buffer = JsonUtility::GetJsonString(root);
	} 
	else
	{
		buffer = "[Call Expr] Calling " + this->FunctionName +  " from file: " + this->FuncDeclFile + " with arguments: \n";
		for (auto elem : this->Arguments)
		{
			buffer += "\t\t" + elem->ToString("") + "\n";
		}
	}
	
	return buffer;
}

void CallExprSt::FromString(string format, string buffer)
{
	if(format=="Json")
	{
		pt::ptree root = JsonUtility::GetJsonObject(buffer);
		this->setText(root.get<string>("Text", "Undefined Text"));
		this->setType(root.get<string>("Type", "Undefined Type"));
		this->setFunctionName(root.get<string>("Called Function", "Undefined Called Function"));
		this->setFuncDeclFile(root.get<string>("Definition File", "Undefined Definition File"));
		for (pt::ptree::value_type &st : root.get_child("Arguments"))
		{
			this->AddArgument(StatementHandler::ReadJsonStatement(st.second));
		}
	}
}

void  CallExprSt::AddArgument(Statement* st)
{
	this->Arguments.push_back(st);
}
