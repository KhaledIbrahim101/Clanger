#ifndef   VIOLATION_H
#define   VIOLATION_H
#include <iostream>
#include <string>
#include <JsonUtility.hpp>
using namespace std;

class Violation  
{
	private:
		string StandardName;
		string RuleName;
		string RuleDescription;
		string Action;

	public:
		string getStandardName();
		void setStandardName(string StandardName);
		string getRuleName();
		void setRuleName(string RuleName);
		string getRuleDescription(); 
		void setRuleDescription(string RuleDescription); 
		string getAction();
		void setAction(string Action);
		bool operator< (const Violation & msgObj) const;
		string ToString(string format);
		void FromString(string format, string buffer);
		Violation();
		~Violation();
};
#endif