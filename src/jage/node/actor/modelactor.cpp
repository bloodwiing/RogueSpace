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
    m_model = AssetManager::getInstance()->get<AssetManager::Types::Model>(fileName, priority);
    m_shader = AssetManager::getInstance()->get<AssetManager::Types::Shader>("./res/default", 100);
}

void ModelActor::draw() {
    m_model->draw(*m_shader, getWorldMatrix());
    DynamicActor::draw();
}
