#pragma once
#include <string>
#include <vector>
#include <map>

class dict {
    public:
        std::string parse(std::string input);
    private:
        std::string input;
        std::vector<std::string> city;
        std::vector<std::string> code;
        std::map<std::string, std::string> map;
};