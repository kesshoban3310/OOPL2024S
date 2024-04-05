#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

#include "Util/GameObject.hpp"
#include "pch.hpp"
#include "ImageObject.hpp"
#include <string>
#include <vector>

namespace TileMap {

const glm::vec2 SCALE = {3, 3};
const glm::vec2 TILE_SIZE = {32, 32};

/**
 *  @brief convert a txt file into a 2D vector
 *  @param path the path of the txt file
 *  @return a 2D vector that stored integer
 */
std::vector<std::vector<int>> ConvertToTiles(const std::string &path);

/**
 * @brief get the position of the tile
 * @param x the x position of the tile
 * @param y the y position of the tile
 * @return the position of the tile
 */
inline glm::vec2 GetTilePosition(const int &x, const int &y);

/**
 * @brief get the vector of GameObjects in the background
 * @param stageName the name of the stage, used to find the stage
 * @return the vector of GameObjects in the background
 */
std::vector<std::shared_ptr<ImageObject>>
GetBackgroundObjects(const std::string &stageName);

/**
 * @brief get the vector of GameObjects in the foreground
 * @param stageName the name of the stage, used to find the stage
 * @return the vector of GameObjects in the foreground
 */
std::vector<std::shared_ptr<ImageObject>>
GetForegroundObjects(const std::string &stageName);

} // namespace TileMap

#endif // TILE_MAP_HPP
