#ifndef DECLREFEXPRST_H
#define DECLREFEXPRST_H 
#include <string>
#ifndef  STATEMENT_H  
#include "Statement.hpp"
#endif
using namespace std;
class DeclRefExprSt : public Statement
{
	private:
		string RefType;

	public:
		DeclRefExprSt();
		~DeclRefExprSt();
		string getRefType();
		void setRefType(string reftype);
		string ToString(string format) override;
		void FromString(string format,string buffer) override;
};
#endif