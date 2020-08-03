#ifndef OPAQUEVALUEEXPRST_H
#define OPAQUEVALUEEXPRST_H 
#include <string>
#ifndef  STATEMENT_H  
#include "Statement.hpp"
#endif
using namespace std;
class OpaqueValueExprSt : public Statement
{
	private:
		Statement* LeftSide;
		Statement* RightSide;
		string OpCode;

	public:
		OpaqueValueExprSt();
		~OpaqueValueExprSt();
		string ToString(string format) override;
		void FromString(string format,string buffer) override;
};
#endif