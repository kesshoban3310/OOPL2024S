#ifndef TXTCONVERTER_HPP
#define TXTCONVERTER_HPP

#include <fstream>
#include <string>
#include <vector>

class Txtconverter{
public:
    /**
    *  @brief Constructor
    *  @param path Give path to convert txt file.
    */
    Txtconverter(const std::string &path);
    /**
    *  @brief convert a txtfile into a vector
    *  @return a vector that stored integer
    */
    std::vector<std::vector<int>> convert();
private:
    std::string Tilepath;
};

#endif
