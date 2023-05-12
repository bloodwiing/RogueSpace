#include "jage/actor/modelactor.hpp"

#include <utility>

#include "jage/runtime/assetmanager.hpp"

using jage::actor::ModelActor;

std::string ModelActor::getTypeName() const {
    return "ModelActor";
}

ModelActor::ModelActor(Scene *scene, abc::ActorABC *parent, std::string name, Tag tag, bool isVolatile, const char *fileName, int priority /* = ASSET_STREAM_BASE_PRIORITY */)
    : DynamicActor(scene, parent, std::move(name), tag, isVolatile)
{
    m_model = jage::runtime::AssetManager::getInstance()->getModel(fileName, priority);
}

void ModelActor::draw(jage::graphics::Shader &shader) {
    m_model->draw(shader, getWorldMatrix());
    DynamicActor::draw(shader);
}
