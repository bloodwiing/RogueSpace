#include "jage/node/frame/basicframe.hpp"

#include <glm/matrix.hpp>

#include "jage/runtime/asset/assetmanager.hpp"

using jage::node::frame::BasicFrame;
using jage::type::RectF;
using jage::graphics::mesh2d::Quad2D;
using jage::runtime::asset::AssetManager;

BasicFrame::BasicFrame(JAGE_FRAME_ARGS)
        : FrameABC(parent, std::move(name), canvas, rectParent, rect, anchor)
{

}

void BasicFrame::scriptUpdate() {
    abc::FrameABC::scriptUpdate();
    updateReflow();
    updateTransformations();
}

void BasicFrame::updateTransformations() {
    if (!m_needsMatrixUpdate)
        return;

    Transformable2DABC::updateTransformations(getParent() != nullptr ? getParent()->getWorldMatrix() : glm::mat3(1.0f));
    m_needsMatrixUpdate = false;

    for (auto& [name, child] : m_children) {
        auto canvasChild = dynamic_cast<BasicFrame*>(child.value.get());
        if (canvasChild != nullptr) {
            canvasChild->markForMatrixUpdate();
        }
    }
}

glm::mat3 BasicFrame::getWorldMatrix() const {
    return m_worldMatrix;
}

glm::vec2 BasicFrame::getTranslation() const {
    return m_translation;
}

float BasicFrame::getRotation() const {
    return m_rotation;
}

glm::vec2 BasicFrame::getScale() const {
    return m_scale;
}

void BasicFrame::setWorldMatrix(const glm::mat3& mat) {
    m_worldMatrix = mat;
}

void BasicFrame::setTranslation(const glm::vec2& tra) {
    m_translation = tra;
    markForMatrixUpdate();
}

void BasicFrame::setRotation(const float& rot) {
    m_rotation = rot;
    markForMatrixUpdate();
}

void BasicFrame::setScale(const glm::vec2& sca) {
    m_scale = sca;
    markForMatrixUpdate();
}

void BasicFrame::markForMatrixUpdate() {
    m_needsMatrixUpdate = true;
}
