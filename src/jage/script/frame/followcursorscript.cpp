#include "jage/script/frame/followcursorscript.hpp"

#include "jage/runtime/window.hpp"

using jage::script::frame::FollowCursorScript;

FollowCursorScript::FollowCursorScript(abc::ScriptableABC *node) {
    validate(node);
}

void FollowCursorScript::onAttach() {

}

void FollowCursorScript::onSpawn() {

}

void FollowCursorScript::onUpdate() {
    double x, y;
    jage::runtime::Window::getActive()->getScreenMouse(x, y);

    m_node->setTranslation(glm::vec2(x, y));
}

void FollowCursorScript::onDeath() {

}
