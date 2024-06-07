#include "Component/PersonLife.hpp"
#include "Component/ImageObject.hpp"

PersonLife::PersonLife() {
    const std::string imagePaths[] = {
        RESOURCE_DIR "/Picture/Item/One_Up.png",
        RESOURCE_DIR "/Picture/UI/Score/equal.png",
        RESOURCE_DIR "/Picture/UI/Score/word0.png",
        RESOURCE_DIR "/Picture/UI/Score/word0.png"};
    m_Children.resize(4);
    for (int i = 0; i < 4; i++) {
        std::shared_ptr<ImageObject> image =
            std::make_shared<ImageObject>(imagePaths[i]);
        image->SetPosition(OFFSETS[i] + glm::vec2{360, -3408});
        image->SetScale(SCALE);
        image->SetZIndex(Z_INDEX);
        m_Children[i] = image;
    }
}

void PersonLife::Update(int life, glm::vec2 cameraPosition) {
    for (int i = 0; i < 4; ++i) {
        std::dynamic_pointer_cast<ImageObject>(m_Children[i])
            ->SetPosition(OFFSETS[i] + cameraPosition);
    }

    if (life > 99)
        life = 99;

    std::string wordPath = RESOURCE_DIR "/Picture/UI/Score/word";
    std::dynamic_pointer_cast<ImageObject>(m_Children[2])
        ->SetImage(wordPath + std::to_string(life / 10) + ".png");
    std::dynamic_pointer_cast<ImageObject>(m_Children[3])
        ->SetImage(wordPath + std::to_string(life % 10) + ".png");
}
