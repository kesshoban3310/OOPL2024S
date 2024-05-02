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

std::vector<std::shared_ptr<TileBox>>
TileMap::GetBackgroundObjects(const std::string &stageName) {
    // initialize result
    std::vector<std::shared_ptr<TileBox>> result;
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
            glm::vec2 objectpos = GetTilePosition(static_cast<int>(x), static_cast<int>(y));
            std::shared_ptr<ImageObject> object = std::make_shared<ImageObject>(
                RESOURCE_DIR "/Picture/Tiles/" + stageName + "/BackGround/" +
                std::to_string(tiles[x][y]) + ".png");
            object->SetPosition(objectpos);
            object->SetScale(SCALE);
            object->SetZIndex(0);

            //Set object into TileBox, Only for Bomb Man Stage.
            TileBox::ObjectType type = TileBox::ObjectType::NORMAL;
            std::shared_ptr<Util::GameObject> boxobject = object;
            std::shared_ptr<TileBox> box = std::make_shared<TileBox>(objectpos,SCALE,boxobject,type);
            result.push_back(box);
        }
    }

    // return result
    return result;
}

// TODO: add collision detection object with object
std::vector<std::shared_ptr<TileBox>>
TileMap::GetForegroundObjects(const std::string &stageName) {
    // initialize result
    std::vector<std::shared_ptr<TileBox>> result;

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
            glm::vec2 objectpos = GetTilePosition(static_cast<int>(x), static_cast<int>(y));
            std::shared_ptr<ImageObject> object = std::make_shared<ImageObject>(
                RESOURCE_DIR "/Picture/Tiles/" + stageName + "/Object/" +
                std::to_string(tiles[x][y]) + ".png");
            object->SetPosition(objectpos);
            object->SetScale(SCALE);
            object->SetZIndex(20);

            //Set object into TileBox, Only for Bomb Man Stage.
            TileBox::ObjectType type = TileBox::ObjectType::WALL;
            switch (tiles[x][y]) {
            case 15:
                type = TileBox::ObjectType::CLIMB;
                break;
            case 16:
                type = TileBox::ObjectType::DAMAGE;
                break;
            }
            std::shared_ptr<Util::GameObject> boxobject = object;
            std::shared_ptr<TileBox> box = std::make_shared<TileBox>(objectpos,SCALE,boxobject,type);
            result.push_back(box);
        }
    }

    // return result
    return result;
}
