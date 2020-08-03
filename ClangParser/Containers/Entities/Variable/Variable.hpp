#ifndef   VARIABLE_H
#define   VARIABLE_H
#include <iostream>
#include <string>
#include <JsonUtility.hpp>
using namespace std;
class Variable  
{
	private:
		string Name;
		string TypeName;
		size_t TypeSize;
		string InitValue;
		string ReferenceType;

	public:
		string getName();
		void setName(string Name);
		string getTypeName();
		void setTypeName(string TypeName);
		size_t getTypeSize();
		void setTypeSize(size_t TypeSize);
		string getInitValue(); 
		void setInitValue(string InitValue); 
		string getReferenceType();
		void setReferenceType(string ReferenceType);
		bool operator< (const Variable & msgObj) const;
		string ToString(string format);
		void FromString(string format, string buffer);
		Variable();
		~Variable();
};
#endif