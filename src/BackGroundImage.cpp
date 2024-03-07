//
// Created by Nick Chang on 2024/3/5.
//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               Buddha Bless         NEVER BUG
//

#include "BackGroundImage.hpp"
#include "Util/Image.hpp"

BackGroundImage::BackGroundImage(const std::string &BackGroundPath) {
    SetImage(BackGroundPath);
}
void BackGroundImage::SetImage(const std::string &BackGroundPath) {
    m_BackGroundPath = BackGroundPath;
    m_Drawable = std::make_shared<Util::Image>(m_BackGroundPath);
    m_Transform.scale = {3,3};
}
[[nodiscard]] const glm::vec2&BackGroundImage::GetPosition() {
    return m_Transform.translation;
}
void BackGroundImage::SetPosition(const glm::vec2& Position) {
    m_Transform.translation = Position;
}