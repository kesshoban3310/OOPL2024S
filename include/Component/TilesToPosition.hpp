

#include "pch.hpp"

glm::vec2 TilesToPosition(int x, int y) {
    return {3 * 16 * x - 3 * 8 * 15, -3 * 16 * y + 3 * 8 * 13};
}
