#include "dict.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

std::string dict::parse(std::string input) {
    std::string temp1;
    std::ifstream myfile("data/airport.txt");
    std::string toReturn = "";
    int count = 0;
    if (!myfile.is_open()) {
        std::cout << "Failed to open input file" << std::endl;
        myfile.close();
        return toReturn;
    }
    if (getline(myfile, temp1).bad() == true) {
        std::cout << "Failed to read input file" << std::endl;
        myfile.close();
        return toReturn;
    }
    while (!myfile.eof()) {
        getline(myfile, temp1, ',');
        if (count % 13 == 2) {
            while (temp1.find('"') != std::string::npos) {
                temp1.erase(temp1.find('"'), 1);
            }
            this->city.push_back(temp1);
        }
        if (count % 13 == 4) {
            while (temp1.find('"') != std::string::npos) {
                temp1.erase(temp1.find('"'), 1);
            }
            this->code.push_back(temp1);
        }
        count++;
    }
    for (unsigned x = 0; x < this->city.size(); x++) {
        if (city[x] == input) {
            toReturn = code[x];
            break;
        } 
    }
    return toReturn;
}
