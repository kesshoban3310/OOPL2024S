#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "glm/glm.hpp"

namespace Tilemap {

constexpr int ROW_TILES_COUNT = 16;
constexpr int COLUMN_TILES_COUNT = 14;
constexpr glm::vec2 SCALE = {3, 3};
constexpr int PIXEL_PER_TILE = 16;

glm::vec2 GetTilePosition(int x, int y);

} // namespace Tilemap

#endif // TILEMAP_HPP
