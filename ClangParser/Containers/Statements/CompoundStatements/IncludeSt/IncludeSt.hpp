#ifndef   INCLUDE_H
#define   INCLUDE_H
#include <string>
#ifndef  STATEMENT_H  
#include "Statement.hpp"
#endif
using namespace std;

class IncludeSt : public Statement
{
	private:
		string IncludeType;
		string FileName;
	public:
		IncludeSt();
		~IncludeSt();
		string getFileName();
		void setFileName(string name);
	    string getIncludeType();
		void setIncludeType(string type);
		string ToString(string format) override;
		void FromString(string format, string buffer) override;
		bool operator< (const IncludeSt & msgObj) const;
};
#endif