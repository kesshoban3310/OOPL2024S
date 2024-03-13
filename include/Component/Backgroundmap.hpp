#ifndef BACK_GROUND_MAP_HPP
#define BACK_GROUND_MAP_HPP

#include "Component/Tilemap.hpp"
#include "ImageObject.hpp"
#include "Util/GameObject.hpp"
#include "pch.hpp"

class Backgroundmap {
public:
    /**
     *  @brief Constructor
     *  @param v Give a 2D matrix to get map.
     *  @param stage Give stage name to load Tile file.
     */
    Backgroundmap(const std::vector<std::vector<int>> &v,
                  const std::string &stage);

    /**
     *  @brief Convert map_num to Map
     *  @param visible Set map visible or unvisable
     */

    void SetImageToMap(const bool &visible);

    /**
     *  @brief Move map by camara
     *  @param dx Move map horizontal by dx
     *  @param dy Move map vertical by dy
     */

    void Move(const int dx, const int dy);

    /**
     *  @brief Get all ImageObject in Map
     *  @return a vector stored all ImageObject
     */

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>>
    GetChildren() const {
        std::vector<std::shared_ptr<Util::GameObject>> ans;
        for (auto i : Map)
            for (auto j : i)
                ans.push_back(j);
        return ans;
    }

private:
    std::vector<std::vector<std::shared_ptr<ImageObject>>>
        Map; // Beta Version. Change After the Map Made.
    std::vector<std::vector<int>> map_num; // Change Number to Image.
    std::string stage;                     // Initial Stage to change Image;
    int left_up, right_down;
};

#endif
