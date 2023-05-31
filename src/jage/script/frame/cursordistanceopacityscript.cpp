#include "jage/script/frame/cursordistanceopacityscript.hpp"

#include "jage/runtime/window.hpp"

using jage::script::frame::CursorDistanceOpacityScript;
using jage::runtime::Window;

CursorDistanceOpacityScript::CursorDistanceOpacityScript(abc::ScriptableABC* node, float minDistance, float maxDistance, float maxOpacity)
        : m_minDistance(minDistance)
        , m_maxDistance(maxDistance)
        , m_maxOpacity(maxOpacity)
{
    validate(node);
}

void CursorDistanceOpacityScript::onAttach() {

}

void CursorDistanceOpacityScript::onSpawn() {

}

void CursorDistanceOpacityScript::onUpdate() {
    double x, y;
    Window::getActive()->getRelativeMouse(x, y);

    float distance = glm::length(glm::vec2(x, y));

    float value = 1.0f - (distance - m_minDistance) / (m_maxDistance - m_minDistance);
    value = glm::clamp(value, 0.0f, 1.0f);

    m_node->setOpacity(value * m_maxOpacity);
}

void CursorDistanceOpacityScript::onDeath() {

}
