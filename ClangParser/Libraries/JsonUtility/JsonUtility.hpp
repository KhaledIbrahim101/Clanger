#ifndef   JSONUTILITY_H
#define   JSONUTILITY_H
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
// Short alias for this namespace
namespace pt = boost::property_tree;

class JsonUtility
{
private:
	JsonUtility(void) {};
	~JsonUtility(void) {};
public:
	static string GetJsonString(pt::ptree root);
	static pt::ptree GetJsonObject(string buffer);
	static string escape_json(const string &s);
};
#endif