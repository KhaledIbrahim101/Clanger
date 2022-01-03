#ifndef   CODEELEMENT_H
#define   CODEELEMENT_H
#ifndef  CODEFILE_H
#include <CodeFile.hpp>
#endif

using namespace std;
class CodeElement  
{
	private:
		uint32_t GID;
		string Name;
		
	public:
		bool Marked;
		string IncludeNames;
		string ElementLinks;
		set<CodeFile> Files;
		CodeElement();
		~CodeElement();
		uint16_t getGID();
		void setGID(uint16_t ID);
		string getName();
		void setName(string Name);
		void AddCodeFile(CodeFile CF);
		string ToString(string format);
		void FromString(string format, string buffer);
		bool operator< (const CodeElement & msgObj) const;
};

class CodeCluster
{
	public:
		uint32_t GID;
		string Name;
		bool Marked;
		set<CodeElement> Elements;
		CodeCluster();
		~CodeCluster();
		string ToString(string format);
		void FromString(string format, string buffer);
		bool operator< (const CodeElement & msgObj) const;
};
#endif