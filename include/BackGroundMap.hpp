#ifndef BACK_GROUND_MAP_HPP
#define BACK_GROUND_MAP_HPP

#include "BackGroundImage.hpp"
#include "pch.hpp"
#include "Util/GameObject.hpp"

class BackGroundMap{
public:
    BackGroundMap(std::vector<std::vector<int>> v,std::string stage);
    void SetImageToMap();
    void Move(const int num);

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
        std::vector<std::shared_ptr<Util::GameObject>> ans;
        for(auto i:Map)
            for(auto j:i)
                ans.push_back(j);
        return ans;
    }
private:
    std::vector<std::vector<std::shared_ptr<BackGroundImage> >> Map; // Beta Version. Change After the Map Made.
    std::vector<std::vector<int>> map_num; //Change Number to Image.
    std::string stage; //Initial Stage to change Image;
    int left_up,right_down;
};


#endif
