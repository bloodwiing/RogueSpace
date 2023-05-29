#include "jage/node/frame/spriteframe.hpp"

#include <glm/gtc/type_ptr.hpp>

#include "jage/runtime/asset/assets.hpp"

using jage::node::frame::SpriteFrame;
using jage::node::frame::SolidFrame;
using jage::graphics::mesh2d::Sprite;
using jage::graphics::mesh2d::Quad2D;
using jage::graphics::Shader;
using jage::runtime::asset::Assets;

SpriteFrame::SpriteFrame(JAGE_FRAME_ARGS, std::shared_ptr<Sprite> sprite)
        : SolidFrame(parent, std::move(name), canvas, rectParent, rect, anchor, Assets::get<Assets::Shader>("./res/shader/ui"), sprite)
        , m_sprite(std::move(sprite))
{

}

SpriteFrame::SpriteFrame(JAGE_FRAME_ARGS, const std::string& filePath)
        : SpriteFrame(parent, std::move(name), canvas, rectParent, rect, anchor, Assets::get<Assets::Sprite>(filePath))
{

}

void SpriteFrame::draw() {
//    if (!m_sprite->apply(*m_shader))
//        return;
//
//    glUniform4fv(m_shader->getUniform("Multiply"), 1, glm::value_ptr(m_multiply));
//    glUniform4fv(m_shader->getUniform("Add"), 1, glm::value_ptr(m_add));
//
//    glUniformMatrix3fv(m_shader->getUniform("UVMatrix"), 1, GL_FALSE, glm::value_ptr(m_uvMatrix));
//
//    glUniform1f(m_shader->getUniform("CropLeft"), m_crop.x1);
//    glUniform1f(m_shader->getUniform("CropBottom"), m_crop.y1);
//    glUniform1f(m_shader->getUniform("CropRight"), m_crop.x2);
//    glUniform1f(m_shader->getUniform("CropTop"), m_crop.y2);
//
//    SolidFrame::draw();
}

void SpriteFrame::setSprite(std::shared_ptr<Sprite> sprite) {
    m_sprite = std::move(sprite);
    m_quad = Quad2D(getScreenRect(), getSprite());
}

void SpriteFrame::setMultiply(glm::vec4 multiply) {
    m_multiply = multiply;
}

void SpriteFrame::setMultiply(float r, float g, float b, float a /* = 1.0f */) {
    setMultiply(glm::vec4(r, g, b, a));
}

void SpriteFrame::setOpacity(float a) {
    m_multiply.a = a;
}

void SpriteFrame::setAdd(glm::vec4 add) {
    m_add = add;
}

void SpriteFrame::setAdd(float r, float g, float b, float a /* = 0.0f */) {
    setAdd(glm::vec4(r, g, b, a));
}

void SpriteFrame::flipHorizontally(bool value) {
    m_flipHor = value;
    updateUVMatrix();
}

void SpriteFrame::flipVertically(bool value) {
    m_flipVer = value;
    updateUVMatrix();
}

void SpriteFrame::setCropLeft(float value) {
    m_crop.x1 = value;
}

void SpriteFrame::setCropBottom(float value) {
    m_crop.y1 = value;
}

void SpriteFrame::setCropRight(float value) {
    m_crop.x2 = value;
}

void SpriteFrame::setCropTop(float value) {
    m_crop.y2 = value;
}

std::shared_ptr<Sprite> SpriteFrame::getSprite() const {
    return m_sprite;
}

glm::vec4 SpriteFrame::getMultiply() const {
    return m_multiply;
}

glm::vec4 SpriteFrame::getAdd() const {
    return m_add;
}

std::shared_ptr<Sprite> SpriteFrame::getInternalSprite() const {
    return getSprite();
}

void SpriteFrame::updateUVMatrix() {
    m_uvMatrix = glm::mat3(1.0f);

    if (m_flipHor) {
        m_uvMatrix[0][0] = -1.0f;
        m_uvMatrix[2][0] = 1.0f;
    }

    if (m_flipVer) {
        m_uvMatrix[1][1] = -1.0f;
        m_uvMatrix[2][1] = 1.0f;
    }
}
