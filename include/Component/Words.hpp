#ifndef WORDS_HPP
#define WORDS_HPP

#include "ImageObject.hpp"
#include <vector>
class Words{
public:
    Words(std::string word,glm::vec2 scale);

    void SetPosition(int idx,glm::vec2 pos);
    glm::vec2 GetPosition(int idx);

    void Show(int idx);
    void ShowAll();

    void Disable(int idx);
    void DisableAll();

    void SetScale(glm::vec2 scales);
    glm::vec2 GetScale();

    std::string GetWords();

    [[nodiscard]]std::vector<std::shared_ptr<Util::GameObject>> GetChildren(){
        std::vector<std::shared_ptr<Util::GameObject>> childrens;
        for(int i=0;i<WordObjects.size();i++){
            childrens.push_back(WordObjects[i]);
        }
        return childrens;
    }
private:
    std::vector<std::shared_ptr<ImageObject>> WordObjects;
    std::string Word;
    std::vector<glm::vec2> WordPositions;
    glm::vec2 WordScale;
<<<<<<< HEAD
=======

>>>>>>> 8f0d4981ffc27b6fa73d868352829e9d60500219
    void SetWords(std::string word);
};

#endif