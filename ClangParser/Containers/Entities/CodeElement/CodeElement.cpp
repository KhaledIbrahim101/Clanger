#include "CodeElement.hpp"  
CodeElement::CodeElement()
{
	GID = 0;
	Marked = false;
	IncludeNames = "";
	ElementLinks = "";
}

CodeElement::~CodeElement()
{

}

uint16_t CodeElement::getGID() 
{
	return this->GID;
}
void CodeElement::setGID(uint16_t ID) 
{
	this->GID = ID;
}

string CodeElement::getName() 
{
	return this->Name;
}
void CodeElement::setName(string Name) 
{
	this->Name = Name;
}

void CodeElement::AddCodeFile(CodeFile CF)
{
	this->Files.insert(CF);
}

bool CodeElement::operator< (const CodeElement & msgObj) const
{
	std::string rightStr = 	msgObj.Name ;
	std::string leftStr = 	this->Name ;
	return (leftStr < rightStr);
}

string CodeElement::ToString(string format)
{
	string buffer = "";
	if(format == "Json")
	{
		pt::ptree root, temp , array;
		root.put("Name", Name);
		
		for (auto elem : this->Files)
		{
			temp = JsonUtility::GetJsonObject(elem.ToString("Json"));
			array.push_back(std::make_pair("", temp));
		}
		root.put_child("Files", array);
		array.clear();

		buffer = JsonUtility::GetJsonString(root);
	}
	else
	{
		buffer ="Element Name: " + Name + "\n" ;
		for (auto elem : this->Files)
		{
			buffer += "[Code File] " + elem.ToString("") + "\n";
		}
		buffer += "---------------------------\n";
		buffer += "---------------------------\n";
	}
	
	return buffer;
}

void CodeElement::FromString(string format, string buffer)
{
	if(format == "Json")
	{
		pt::ptree root = JsonUtility::GetJsonObject(buffer);
		this->setName(root.get<string>("Name", "Undefined Name"));
		
		for (pt::ptree::value_type &st : root.get_child("Files"))
		{
			CodeFile* file = new CodeFile();
			file->FromString("Json",JsonUtility::GetJsonString(st.second));
			Files.insert(*file);
		}
	}
	else
	{
		/* code */
	}
}

CodeCluster::CodeCluster()
{
	GID = 0;
	Marked = false;
}

CodeCluster::~CodeCluster()
{

}
