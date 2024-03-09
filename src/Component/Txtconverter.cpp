//
// Created by User on 2024/3/9.
//

#include "Component/Txtconverter.hpp"
Txtconverter::Txtconverter(const std::string &path) {
    this->Tilepath = path;
}

std::vector<std::vector<int>> Txtconverter::convert() {
    std::ifstream txtfile;
    txtfile.open(Tilepath);
    std::vector<std::vector<int> > vec;
    std::string txt_log;
    while(std::getline(txtfile,txt_log)){ //read each line in txtfile
        std::vector<int> column;
        std::string number = "";
        for(auto vb:txt_log){
            if(vb != ' ') { // if char != vb, then store to number.
                number+=vb;
            }
            else {
                column.push_back(std::atoi(number.c_str())); // convert number type from string to integer and store to column.
                number = "";
            }
        }
        if(number != ""){
            column.push_back(std::atoi(number.c_str()));
        }
        vec.push_back(column); //store each line's number into vector.
    }
    return vec;
}