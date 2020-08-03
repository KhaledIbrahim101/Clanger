#ifndef   DECLST_H
#define   DECLST_H
#include <string>
#ifndef  STATEMENT_H  
#include "Statement.hpp"
#endif
using namespace std;
class DeclSt : public Statement
{
	private:
		string Entity;

	public:
		DeclSt();
		~DeclSt();
		string getEntity();
		void setEntity(string Entity);
	    string ToString(string format) override;
		void FromString(string format, string buffer) override;
};
#endif