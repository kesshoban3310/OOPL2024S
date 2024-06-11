#ifndef WORDS_HPP
#define WORDS_HPP

#include "ImageObject.hpp"
#include <vector>
class Words{
public:
    Words(std::string word);
    void SetPosition(int idx,glm::vec2 pos);
    glm::vec2 GetPosition(int idx);
    void Show(int idx);
    void ShowAll();
    void Disable(int idx);
    void DisableAll();
    [[nodiscard]]std::vector<std::shared_ptr<Util::GameObject>> GetChildren(){
        std::vector<std::shared_ptr<Util::GameObject>> childrens;
        for(int i=0;i<WordObjects.size();i++){
            childrens.push_back(WordObjects[i]);
        }
        return childrens;
    }
private:
    std::vector<std::shared_ptr<ImageObject>> WordObjects;
    std::vector<std::string> WordStrings;
    std::vector<glm::vec2> WordPositions;
};

#endif
