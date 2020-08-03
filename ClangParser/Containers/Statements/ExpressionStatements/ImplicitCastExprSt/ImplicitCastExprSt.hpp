#ifndef IMPLICITCASTEXPRST_H
#define IMPLICITCASTEXPRST_H 
#include <string>
#ifndef  STATEMENT_H  
#include "Statement.hpp"
#endif
using namespace std;
class ImplicitCastExprSt : public Statement
{
	private:
		string RefType;

	public:
		ImplicitCastExprSt();
		~ImplicitCastExprSt();
		string getRefType();
		void setRefType(string reftype);
		string ToString(string format) override;
		void FromString(string format,string buffer) override;
};
#endif