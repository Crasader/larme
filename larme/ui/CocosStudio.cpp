#include "CocosStudio.hpp"

namespace larme {
namespace ui {

Node* CocosStudio::loadFromCsb(const char* resourceName) {
    //CSLoader::getInstance()->setRecordJsonPath(true);
    auto node = CSLoader::getInstance()->createNode(resourceName);
    node->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    return node;
}
    
}// namespace ui
}// namespace larme