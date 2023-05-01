#include "engine/actor/modelactor.hpp"

#include <utility>

#include "engine/assetmanager.hpp"

namespace Actors = Engine::Actors;

std::string Actors::ModelActor::getTypeName() const {
    return "ModelActor";
}

Actors::ModelActor::ModelActor(Engine::Scene *scene, Actors::ActorBase *parent, std::string name, const char *fileName)
    : DynamicActor(scene, parent, std::move(name))
{
    m_model = Engine::AssetManager::getInstance()->getModel(fileName);
}

void Actors::ModelActor::draw(Graphics::Shader &shader) {
    m_model->draw(shader, DynamicActor::getWorldMatrix());
}
