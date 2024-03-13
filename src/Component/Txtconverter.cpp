#include "Component/Txtconverter.hpp"

Txtconverter::Txtconverter(const std::string &path) {
    this->Tilepath = path;
}

std::vector<std::vector<int>> Txtconverter::convert() {
    std::ifstream txtfile;
    txtfile.open(Tilepath);
    std::vector<std::vector<int>> vec;
    std::string txt_log;
    // read each line in txtfile
    while (std::getline(txtfile, txt_log)) {
        std::vector<int> column;
        std::string number = "";
        for (auto vb : txt_log) {
            // if char != vb, then store to number.
            if (vb != ' ') {
                number += vb;
            }
            else {
                // convert number type from string to
                // integer and store to column.
                column.push_back(std::atoi(number.c_str()));
                number = "";
            }
        }
        if (number != "") {
            column.push_back(std::atoi(number.c_str()));
        }
        vec.push_back(column); // store each line's number into vector.
    }
    return vec;
}
