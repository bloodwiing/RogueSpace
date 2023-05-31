#include "jage/script/frame/followcursorscript.hpp"

#include "jage/runtime/window.hpp"

using jage::script::frame::FollowCursorScript;

FollowCursorScript::FollowCursorScript(abc::ScriptableABC* node, float maxDistance)
        : m_maxDistance(maxDistance)
{
    validate(node);
}

void FollowCursorScript::onAttach() {

}

void FollowCursorScript::onSpawn() {

}

void FollowCursorScript::onUpdate() {
    double u, v;
    jage::runtime::Window::getActive()->getScreenMouse(u, v);

    double x, y;
    jage::runtime::Window::getActive()->getRelativeMouse(x, y);

    auto point = glm::vec2(u, v);
    if (m_maxDistance != -1.0f) {
        point = point / (glm::max(glm::length(glm::vec2(x, y)), m_maxDistance) / m_maxDistance);
    }

    m_node->setTranslation(point);
}

void FollowCursorScript::onDeath() {

}
