//
// Created by User on 2024/6/10.
//
#include "Component/Words.hpp"
#include "Util/Logger.hpp"
Words::Words(std::string word) {
    for(int i=0;i<word.size();i++){
        std::string WordPath = RESOURCE_DIR "/Picture/UI/Alphabet/" + std::string(1,word[i]) + ".png";
        std::shared_ptr<ImageObject> WordImg = std::make_shared<ImageObject>(WordPath);
        WordImg->SetPosition({0,0});
        WordImg->SetScale({3,3});
        WordImg->SetZIndex(80);
        WordImg->SetVisible(false);
        WordObjects.push_back(WordImg);
        WordPositions.push_back(glm::vec2 {0,0});
        WordStrings.push_back(WordPath);
    }
}


void Words::SetPosition(int idx,glm::vec2 pos){
    WordObjects[idx]->SetPosition(pos);
    WordPositions[idx] = pos;
}
glm::vec2 Words::GetPosition(int idx){
    return WordPositions[idx];
}
void Words::Show(int idx){
    WordObjects[idx]->SetVisible(true);
}
void Words::ShowAll(){
    for(auto i:WordObjects){
        i->SetVisible(true);
    }
}
void Words::Disable(int idx){
    WordObjects[idx]->SetVisible(false);
}
void Words::DisableAll(){
    for(auto i:WordObjects){
        i->SetVisible(false);
    }
}
