#ifndef   BINARYOPERATORST_H
#define   BINARYOPERATORST_H
#include <string>
#ifndef  STATEMENT_H  
#include "Statement.hpp"
#endif
using namespace std;
class BinaryOperatorSt : public Statement
{
	private:
		Statement* LeftSide;
		Statement* RightSide;
		string OpCode;

	public:
		BinaryOperatorSt();
		~BinaryOperatorSt();
		Statement* getLeftSide();
		void setLeftSide(Statement* LeftSide);
		Statement* getRightSide();
		void setRightSide(Statement* RightSide);
		string getOpCode();
		void setOpCode(string OpCode);
		string ToString(string format) override;
		void FromString(string format, string buffer) override;
};
#endif