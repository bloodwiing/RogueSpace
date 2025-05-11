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

    const auto cameraMatrix = Camera::getActiveCamera()->getViewMatrix();

    const auto aspectRatio = Window::getActive()->getAspectRatio();

    for (int i = 0; i < m_sprites.size(); ++i) {
        if (i >= enemies.size()) {
            m_sprites[i]->setOpacity(0.0f);
            continue;
        }

        /*
         *
        const auto clipPos = matrix * glm::vec4(enemies[i]->getWorldPosition(), 0.0);
        const auto screenPos = glm::normalize(glm::vec2(clipPos));

        auto spritePos = glm::vec2(
                screenPos.x / glm::max(aspectRatio, 1.0f) * (float)Window::getActive()->getWidth(),
                screenPos.y / glm::max(1 / aspectRatio, 1.0f) * (float)Window::getActive()->getHeight());

         */

        const auto clipPos = cameraMatrix * enemies[i]->getWorldMatrix() * glm::vec4(0, 0, 0, 1.0);
        auto ndc = glm::vec2(clipPos / clipPos.w);

        if (clipPos.z < 0.0f) {
            ndc.x = -ndc.x;
            ndc.y = -ndc.y;
        }

        const auto screenPos = glm::vec2(
                ndc.x * (float)Window::getActive()->getWidth(),
                ndc.y * (float)Window::getActive()->getHeight());

        const auto normalScreenPos = glm::normalize(screenPos);

        auto spritePos = glm::vec2(
                normalScreenPos.x / glm::max(aspectRatio, 1.0f) * (float)Window::getActive()->getWidth(),
                normalScreenPos.y / glm::max(1 / aspectRatio, 1.0f) * (float)Window::getActive()->getHeight()
                );

        const auto opacityRing = glm::max(aspectRatio, 1.0f) * (float)Window::getActive()->getWidth() * 0.25f;
        const auto oapcityTransition = opacityRing * 0.75f;

        m_sprites[i]->setTranslation(spritePos);
        m_sprites[i]->setRotation(glm::acos(normalScreenPos.x) * (normalScreenPos.y >= 0.0f ? 1.0f : -1.0f) - glm::pi<float>() * 0.5f);
        m_sprites[i]->setScale(glm::vec2(1.0f) * (0.8f + clipPos.z * 0.001f));
        if (clipPos.z < 0.0f) {
            m_sprites[i]->setOpacity(1.0f);
        } else {
            m_sprites[i]->setOpacity(glm::clamp(glm::length(glm::vec2(screenPos)) / oapcityTransition - 0.75f, 0.0f, 1.0f));
        }
    }

    FrameABC::update();
}
