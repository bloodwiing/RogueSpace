#include "jage/node/frame/enemyindicatorframe.hpp"

#include "jage/script/actor/enemyspawnerscript.hpp"
#include "jage/node/frame/anchor.hpp"
#include "jage/node/actor/camera.hpp"
#include "jage/runtime/window.hpp"

using jage::node::frame::EnemyIndicatorFrame;
using jage::script::actor::EnemySpawnerScript;
using jage::type::RectI32;
using jage::node::frame::Anchor;
using jage::node::actor::Camera;
using jage::runtime::Window;

EnemyIndicatorFrame::EnemyIndicatorFrame(JAGE_FRAME_ARGS)
        : BasicFrame(parent, std::move(name), canvas, rectParent, rect, anchor)
{

}

void EnemyIndicatorFrame::update() {
    const auto enemies = EnemySpawnerScript::getEnemies();

    int toAdd = (int)enemies.size() - (int)m_sprites.size();
    for (; toAdd > 0; --toAdd) {
        auto sprite = addChild<SpriteFrame>("Indicator", RectI32::Grow(m_rect.middle(), 50, 50), Anchor::MiddleCenter, "./res/sprite/hud/EnemyIndicator.sprite");

        m_sprites.push_back(sprite);
    }

    const auto matrix = Camera::getActiveCamera()->getViewMatrix();

    const auto aspectRatio = Window::getActive()->getAspectRatio();

    for (int i = 0; i < m_sprites.size(); ++i) {
        if (i >= enemies.size()) {
            m_sprites[i]->setOpacity(0.0f);
            continue;
        }

        const auto clipPos = matrix * glm::vec4(enemies[i]->getWorldPosition(), 0.0);
        const auto screenPos = glm::normalize(glm::vec2(clipPos));

        auto spritePos = glm::vec2(
                screenPos.x / glm::max(aspectRatio, 1.0f) * (float)Window::getActive()->getWidth(),
                screenPos.y / glm::max(1 / aspectRatio, 1.0f) * (float)Window::getActive()->getHeight());

        m_sprites[i]->setTranslation(spritePos);
        m_sprites[i]->setRotation(glm::acos(screenPos.x) * (screenPos.y >= 0.0f ? 1.0f : -1.0f) - glm::pi<float>() * 0.5f);
        m_sprites[i]->setScale(glm::vec2(1.0f) * (0.8f + clipPos.z * 0.001f));
        m_sprites[i]->setOpacity(glm::clamp(glm::length(glm::vec2(clipPos)) * 0.05f - 3.0f, 0.0f, 1.0f));
    }

    FrameABC::update();
}
