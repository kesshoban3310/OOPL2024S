//
// Created by User on 2024/3/5.
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

#include "BackGround.hpp"
#include "Util/Image.hpp"

BackGround::BackGround(const std::string &BackGroundPath) {
    SetImage(BackGroundPath);
}
void BackGround::SetImage(const std::string &BackGroundPath) {
    m_BackGroundPath = BackGroundPath;
    m_Drawable = std::make_shared<Util::Image>(m_BackGroundPath);
}
[[nodiscard]] const glm::vec2& BackGround::GetPosition() {
    return m_Transform.translation;
}
void BackGround::SetPosition(const glm::vec2& Position) {
    m_Transform.translation = Position;
}