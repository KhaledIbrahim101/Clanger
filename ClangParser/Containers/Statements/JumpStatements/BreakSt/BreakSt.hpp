#ifndef BREAKST_H
#define BREAKST_H
#include <string>
#ifndef  STATEMENT_H  
#include "Statement.hpp"
#endif
using namespace std;
class BreakSt : public Statement
{
	private:
		string BreakText;

	public:
		BreakSt();
		~BreakSt();
		string getBreakText();
		void setBreakText(string BreakText);
	    string ToString(string format) override;
		void FromString(string format,string buffer) override;
};
#endif