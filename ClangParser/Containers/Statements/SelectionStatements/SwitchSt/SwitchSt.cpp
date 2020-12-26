#include "SwitchSt.hpp"  
#include "StatementHandler.hpp"
SwitchSt::SwitchSt()
{

}

SwitchSt::~SwitchSt()
{

}

void SwitchSt::setSwitchVariable(Statement* SV)
{
    this->SwitchVariable = SV;
}

Statement* SwitchSt::getSwitchVariable()
{
    return this->SwitchVariable;
}

void SwitchSt::AddSwitchValue(Statement* value)
{
    this->SwitchValues.push_back(value);
}

void SwitchSt::AddSwitchCase(list<Statement*> casebody)
{
    this->SwitchCases.push_back(casebody);
}

list<list<Statement*>> SwitchSt::getSwitchCases()
{
    return this->SwitchCases;
}

string SwitchSt::ToString(string format) 
{
    string buffer = "";
	if(format == "Json")
	{
		pt::ptree root, temp , array, casept,cases;
		root.put("Type", this->getType());
        list<Statement*>::iterator it = SwitchValues.begin();
		for(auto casebody : this->SwitchCases)
        {
            if(it == SwitchValues.end())
            {
                Statement* defsts = new Statement();
                defsts->setText("default:");
                defsts->setType("Default");
                temp = JsonUtility::GetJsonObject(defsts->ToString("Json"));
            }
            else
            {
                temp = JsonUtility::GetJsonObject((*it)->ToString("Json"));
            }
		    casept.put_child("Case Expression",temp);

            for(auto cst : casebody)
            {
                temp = JsonUtility::GetJsonObject(cst->ToString("Json"));
			    array.push_back(std::make_pair("", temp));
                /*temp = JsonUtility::GetJsonObject(cst->ToString("Json"));
                pair<string,pt::ptree> pptree("Statement",temp);
                array.push_back(pptree);*/
            }
            
            casept.put_child("Statements", array);
            cases.put_child("Case", casept);
            casept.clear();
		    array.clear();		    
            advance(it, 1);
        }
        root.put_child("Cases", cases);
        buffer = JsonUtility::GetJsonString(root);
	}
	else
	{
        buffer = "[Switch] switch()\n"  /*this->SwitchVariable->getText()*/  ;
        for(auto casebody : this->SwitchCases)
        {
            for(auto cst : casebody)
            {
                buffer += "\t" + cst->ToString("");
            }
        }
    }
    
	return buffer; 
}

void SwitchSt::FromString(string format,string buffer)
{
    if(format=="Json")
    {
        pt::ptree root = JsonUtility::GetJsonObject(buffer);
        //this->setText(root.get<string>("Text", "Undefined Text"));
		this->setType(root.get<string>("Type", "Undefined Type"));
		for (pt::ptree::value_type &st : root.get_child("Cases"))
		{
            list<Statement*> cStatements;
            pt::ptree temp = st.second.get_child("Case Expression");
            if(!temp.empty())
            {
                this->AddSwitchValue(StatementHandler::ReadJsonStatement(temp));
            }
            
            for (pt::ptree::value_type &stst : st.second.get_child("Statements"))
		    {
                cStatements.push_back(StatementHandler::ReadJsonStatement(stst.second));
            }
            if(!cStatements.empty())
                this->AddSwitchCase(cStatements);
        }
    }
}