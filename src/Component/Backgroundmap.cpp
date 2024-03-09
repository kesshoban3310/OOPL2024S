//
// Created by User on 2024/3/6.
//

#include "Component/Backgroundmap.hpp"
#include "Component/Tilemap.hpp"
#include "Util/Logger.hpp"

Backgroundmap::Backgroundmap(const std::vector<std::vector<int>> &v,const std::string &stage) {
    this->map_num = v;
    this->stage = stage;
}

void Backgroundmap::SetImageToMap(const bool &visable) {
    int n = map_num.size(), m = map_num[0].size();
    std::string Image_path = RESOURCE_DIR"/Picture/Tiles/" + stage;
    for(int i=0;i<n;i++){
        std::vector<std::shared_ptr<ImageObject> > tmp;
        for(int j=0;j<m;j++){
            std::shared_ptr<ImageObject> Block = std::make_shared<ImageObject>(Image_path+"/BackGround/"+std::to_string(map_num[i][j])+".png");
            Block->SetScale({3,3});
            Block->SetZIndex(-10);
            Block->SetPosition(Tilemap::GetTilePosition(j,i));
            Block->SetVisible(visable);
            tmp.push_back(Block);
        }
        Map.push_back(tmp);
    }
}
void Backgroundmap::Move(const int dx,const int dy) {
    int n = map_num.size(), m = map_num[0].size();
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            auto Image_block = Map[i][j];
            auto pos = Image_block->GetPosition();
            Image_block->SetPosition({pos.x+dx,pos.y+dy});
        }
    }
}
