#include <sstream>
#include <iostream>
#include "JsonUtility.hpp"

string JsonUtility::GetJsonString(pt::ptree root)
{
    stringstream ss;
    pt::json_parser::write_json(ss, root);
    return ss.str();
}

pt::ptree JsonUtility::GetJsonObject(string buffer)
{
    pt::ptree root;
    stringstream ss;
    ss << buffer;
    pt::read_json(ss, root);
    return root;
}

string JsonUtility::escape_json(const string &s)
{
    std::ostringstream o;
    for (auto c = s.cbegin(); c != s.cend(); c++) {
        if (*c == '"' || *c == '\\' || ('\x00' <= *c && *c <= '\x1f')) {
            o << "\\u"
            << std::hex << std::setw(4) << std::setfill('0') << (int)*c;
        } else {
            o << *c;
        }
    }
    return o.str();
}
