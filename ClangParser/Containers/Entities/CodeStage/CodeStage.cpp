#include "CodeStage.hpp"  
#include "StatementHandler.hpp"  
CodeStage::CodeStage()
{

}

CodeStage::~CodeStage()
{

}

string CodeStage::getName() 
{
	return this->Name;
}
void CodeStage::setName(string Name) 
{
	this->Name = Name;
}

bool CodeStage::operator< (const CodeStage & msgObj) const
{
	string rightStr =  msgObj.StageFunction->ToString("Json");
	string leftStr = 	this->StageFunction->ToString("Json");
	return (leftStr < rightStr);
}

string CodeStage::ToString(string format)
{
	string buffer = "";
    if(this->StageFunction != nullptr)
    {
        if(format=="Json")
        {
            pt::ptree root, temp , array;
            root.put("File", this->StageFile.getName());
            temp = JsonUtility::GetJsonObject(this->StageFunction->ToString("Json"));
            root.add_child("Function",temp);
            for (auto elem : this->Stages)
            {
                temp = JsonUtility::GetJsonObject(elem->ToString("Json"));
                pair<string,pt::ptree> pptree("Stage",temp);
                array.push_back(pptree);
            }
            root.put_child("Stages", array);
            array.clear();
            buffer = JsonUtility::GetJsonString(root);
        }
        else
        {

        }
    }
	return buffer;
}

void CodeStage::FromString(string format, string buffer)
{
    if(format=="Json")
    {
        Function* fun = new Function();
        pt::ptree root = JsonUtility::GetJsonObject(buffer);
        this->StageFile.setName(root.get<string>("File", "Undefined File"));
        pt::ptree temp = root.get_child("Function");
        fun->FromString("Json",JsonUtility::GetJsonString(temp));
        this->StageFunction = fun;
        for (pt::ptree::value_type &st : root.get_child("Stages"))
		{
            CodeStage* cs = new CodeStage();
            cs->FromString("Json",JsonUtility::GetJsonString(st.second));
			this->Stages.push_back(cs);
		}
    }
}