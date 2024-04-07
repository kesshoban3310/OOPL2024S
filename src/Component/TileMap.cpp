#include "Component/TileMap.hpp"
#include "Component/ImageObject.hpp"
#include "Util/LoadTextFile.hpp"
#include <sstream>

std::vector<std::vector<int>> TileMap::ConvertToTiles(const std::string &path) {
    std::vector<std::vector<int>> result;

    // load text file into stream
    std::string text = Util::LoadTextFile(path);
    std::istringstream stream(text);
    std::string line;

    // convert stream into lines
    while (std::getline(stream, line)) {
        std::vector<int> row_result;
        std::istringstream line_stream(line);
        std::string token;

        // convert line into tokens
        while (std::getline(line_stream, token, ' '))
            row_result.push_back(std::stoi(token));
        result.push_back(row_result);
    }

    // return result
    return result;
}

glm::vec2 TileMap::GetTilePosition(const int &x, const int &y) {
    double positionX = 0.5 * SCALE.y * TILE_SIZE.y * y;
    double positionY = -0.5 * SCALE.x * TILE_SIZE.x * x;
    return {positionX, positionY};
}

std::vector<std::shared_ptr<ImageObject>>
TileMap::GetBackgroundObjects(const std::string &stageName) {
    // initialize result
    std::vector<std::shared_ptr<ImageObject>> result;

    // load tiles
    std::vector<std::vector<int>> tiles =
        ConvertToTiles(RESOURCE_DIR "/Map/BackGround/" + stageName + ".txt");

    // set object objects
    for (std::size_t x = 0; x < tiles.size(); x++) {
        for (std::size_t y = 0; y < tiles[x].size(); y++) {
            // skip empty tiles
            if (tiles[x][y] == 0)
                continue;

            // set object
            std::shared_ptr<ImageObject> object = std::make_shared<ImageObject>(
                RESOURCE_DIR "/Picture/Tiles/" + stageName + "/BackGround/" +
                std::to_string(tiles[x][y]) + ".png");
            object->SetPosition(
                GetTilePosition(static_cast<int>(x), static_cast<int>(y)));
            object->SetScale(SCALE);
            object->SetZIndex(0);
            result.push_back(object);
        }
    }

    // return result
    return result;
}

// TODO: add collision detection object with object
std::vector<std::shared_ptr<ImageObject>>
TileMap::GetForegroundObjects(const std::string &stageName) {
    // initialize result
    std::vector<std::shared_ptr<ImageObject>> result;

    // load tiles
    std::vector<std::vector<int>> tiles =
        ConvertToTiles(RESOURCE_DIR "/Map/Object/" + stageName + ".txt");

    // set object objects
    for (std::size_t x = 0; x < tiles.size(); x++) {
        for (std::size_t y = 0; y < tiles[x].size(); y++) {
            // skip empty tiles
            if (tiles[x][y] == 0)
                continue;

            // set object
            std::shared_ptr<ImageObject> object = std::make_shared<ImageObject>(
                RESOURCE_DIR "/Picture/Tiles/" + stageName + "/Object/" +
                std::to_string(tiles[x][y]) + ".png");
            object->SetPosition(
                GetTilePosition(static_cast<int>(x), static_cast<int>(y)));
            object->SetScale(SCALE);
            object->SetZIndex(20);
            result.push_back(object);
        }
    }

    // return result
    return result;
}
