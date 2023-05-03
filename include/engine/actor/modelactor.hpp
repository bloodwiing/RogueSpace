#ifndef MODEL_ACTOR_CLASS_H
#define MODEL_ACTOR_CLASS_H

#include "dynamicactor.hpp"

#include "engine/assetstream.hpp"

#include "graphics/model.hpp"

namespace Engine::Actors {

    class ModelActor : public DynamicActor {
    public:
        ModelActor(Scene *scene, ActorBase *parent, std::string name, const char *fileName, int priority = ASSET_STREAM_BASE_PRIORITY);

        void draw(Graphics::Shader &shader) override;

    protected:
        [[nodiscard]] std::string getTypeName() const override;

        std::shared_ptr<Graphics::Model> m_model;
    };
}

#endif //MODEL_ACTOR_CLASS_H
