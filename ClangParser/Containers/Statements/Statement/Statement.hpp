#ifndef   STATEMENT_H
#define   STATEMENT_H
#include <string>
#include <JsonUtility.hpp>
#include <StringUtility.hpp>

using namespace std;

class Statement  
{
	private:
		string Text;
		string Type;
	public:
		Statement();
		Statement(string text, string type);
		~Statement();
		string getText();
		void setText(string text);
		string getType();
		void setType(string type);
		pt::ptree GetInitialpTree();
	    virtual string ToString(string format);	
		virtual void FromString(string format, string buffer);	
};
#endif