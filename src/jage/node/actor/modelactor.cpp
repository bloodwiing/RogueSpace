#include "jage/node/actor/modelactor.hpp"

#include <utility>

#include "jage/runtime/asset/assetmanager.hpp"

using jage::node::actor::ModelActor;
using jage::runtime::asset::AssetManager;

std::string ModelActor::getTypeName() const {
    return "ModelActor";
}

ModelActor::ModelActor(JAGE_ACTOR_ARGS, const char *fileName, int priority /* = ASSET_STREAM_BASE_PRIORITY */)
    : DynamicActor(parent, std::move(name), scene, tag, isVolatile)
{
    m_model = AssetManager::getInstance()->get<jage::graphics::model::Model>(fileName, priority);
}

void ModelActor::draw(jage::graphics::Shader &shader) {
    m_model->draw(shader, getWorldMatrix());
    DynamicActor::draw(shader);
}
