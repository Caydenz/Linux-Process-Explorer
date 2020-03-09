#pragma once

#include <string>
#include <sstream>

class Utils {
public:
    static std::string readFile(const std::string& path);
    static std::string getProcValue(std::string key, std::string file, std::istringstream &stream, int position);

};
