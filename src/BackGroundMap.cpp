//
// Created by User on 2024/3/6.
//

#include "BackGroundMap.hpp"
#include "Util/Logger.hpp"

BackGroundMap::BackGroundMap(std::vector<std::vector<int>> v, std::string stage) {
    this->map_num = v;
    this->stage = stage;
}

void BackGroundMap::SetImageToMap() {
    int n = map_num.size(), m = map_num[0].size();
    std::string Image_path = RESOURCE_DIR"/Picture/Tiles/" + stage;
    int x = -15,y = 13; // x = -3*15,y = 3*13. Initial Block will be left up.
    bool show = true;
    for(int i=0;i<n;i++){
        std::vector<std::shared_ptr<BackGroundImage> > tmp;
        for(int j=0;j<m;j++){
            std::shared_ptr<BackGroundImage> Block = std::make_shared<BackGroundImage>(Image_path+"/BackGround/"+std::to_string(map_num[i][j])+".png");
            Block->SetZIndex(-10);
            Block->SetPosition({x*8*3,y*8*3});
            Block->SetVisible(show);
            tmp.push_back(Block);
            x+=2;
            show = not show;
        }
        y-=2;
        x = -15;
        Map.push_back(tmp);
    }
}
void BackGroundMap::Move(const int dx,const int dy) {
    int n = map_num.size(), m = map_num[0].size();
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            auto Image_block = Map[i][j];
            auto pos = Image_block->GetPosition();
            Image_block->SetPosition({pos.x+dx,pos.y+dy});
        }
    }
}
