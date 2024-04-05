//
// Created by User on 2024/4/5.
//


#include "Component/Scorebar.hpp"


Scorebar::Scorebar(glm::vec2 pos){
    position = {pos.x-46,pos.y+312};
    for(int i=0;i<7;i++){
        std::string path = RESOURCE_DIR "/Picture/UI/Score/word" + std::to_string(score[i]) + ".png";
        std::shared_ptr<ImageObject> ScoreImage = std::make_shared<ImageObject>(path);
        ScoreImage->SetScale(scale);
        ScoreImage->SetPosition({pos.x+8*(6-i)*3,pos.y});
        ScoreImage->SetVisible(true);
        ScoreImage->SetZIndex(ZIndex);
        scoreImage.push_back(ScoreImage);
        scoreObject.push_back(ScoreImage);
    }
}
void Scorebar::AddScore(int point) {
    int c = 0,index = 0;
    while(index < 7){
        score[index] = score[index] + point%10 + c;
        c = 0;
        point/=10;
        if(score[index]>=10){
            c = 1;
            score[index] %= 10;
        }
        index++;
        if(!point && !c) break;
    }
    //if(index<7)
        //score[index] = score[index] + point%10 + c;
}
void Scorebar::Show(glm::vec2 pos){
    position = {pos.x-46,pos.y+312};
    for(int i=0;i<7;i++){
        std::string path = RESOURCE_DIR "/Picture/UI/Score/word" + std::to_string(score[i]) + ".png";
        scoreImage[i]->SetImage(path);
        scoreImage[i]->SetPosition({position.x+8*(6-i)*3,position.y});
    }
}