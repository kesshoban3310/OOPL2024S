#ifndef BACK_GROUND_MAP_HPP
#define BACK_GROUND_MAP_HPP

#include "Component/TileMap.hpp"
#include "ImageObject.hpp"
#include "Util/GameObject.hpp"
#include "pch.hpp"
#include "Component/Collider.hpp"

class Backgroundmap {
public:
    /**
     *  @brief Constructor
     *  @param v Give a 2D matrix to get map.
     *  @param stage Give stage name to load Tile file.
     */
    Backgroundmap(const std::string &stage);

    /**
     *  @brief Get map objects
     */

    void SetImagetoBackgroundObject();

    /**
     *  @brief Get map objects
     */

    void SetImagetoForegroundObject();

    /**
     *  @brief Get all ImageObject in Map
     *  @return a vector stored all ImageObject
     */

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>>
    GetChildren() const {
        std::vector<std::shared_ptr<Util::GameObject>> ans;
        for (auto i : Map)
            ans.push_back(i);
        return ans;
    }
    void SetObjectCollisonBox();
    std::vector<std::shared_ptr<Collider>> GetCollisonBox(glm::vec2 camerapos);
private:
    std::vector<std::shared_ptr<ImageObject>> Map; // Beta Version. Change After the Map Made.
    std::vector<std::shared_ptr<Collider>> MapCollisonBox;
    std::string stage;                     // Initial Stage to change Image;
};

#endif
