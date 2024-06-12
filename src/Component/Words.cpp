//
// Created by User on 2024/6/10.
//
#include "Component/Words.hpp"
#include "Util/Logger.hpp"
Words::Words(std::string word,glm::vec2 scale) {
    WordScale = scale;
    SetWords(word);
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
void Words::SetScale(glm::vec2 scales){
    WordScale = scales;
    for(auto i:WordObjects){
        i->SetScale(WordScale);
    }
}
glm::vec2 Words::GetScale() {
    return WordScale;
}

void Words::SetWords(std::string word){
    for(int i=0;i<word.size();i++){
        std::string WordPath;
        if('a'<= word[i] && word[i]<='z')
            WordPath = RESOURCE_DIR "/Picture/UI/Alphabet/" + std::string(1,word[i]) + ".png";
        else
            WordPath = RESOURCE_DIR "/Picture/UI/Alphabet/blank.png";
        std::shared_ptr<ImageObject> WordImg = std::make_shared<ImageObject>(WordPath);
        WordImg->SetPosition({0,0});
        WordImg->SetScale(WordScale);
        WordImg->SetZIndex(80);
        WordImg->SetVisible(false);
        WordObjects.push_back(WordImg);
        WordPositions.push_back(glm::vec2 {0,0});
        Word = word;
    }
}

std::string Words::GetWords(){
    return Word;
}
