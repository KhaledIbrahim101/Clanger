#ifndef RETURNST_H
#define RETURNST_H
#include <string>
#ifndef  STATEMENT_H  
#include "Statement.hpp"
#endif
using namespace std;
class ReturnSt : public Statement
{
	private:
		string ReturnText;

	public:
		ReturnSt();
		~ReturnSt();
		string getReturnText();
		void setReturnText(string ReturnText);
	    string ToString(string format) override;
		void FromString(string format, string buffer) override;
};
#endif