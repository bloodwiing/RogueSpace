#ifndef MODEL_ACTOR_CLASS_H
#define MODEL_ACTOR_CLASS_H

#include "dynamicactor.hpp"

#include "graphics/model.hpp"

namespace Engine::Actors {

    class ModelActor : public DynamicActor {
    public:
        ModelActor(Scene *scene, ActorBase *parent, std::string name, const char *fileName);

        void draw(Graphics::Shader &shader) override;

    protected:
        [[nodiscard]] std::string getTypeName() const override;

    private:
        std::shared_ptr<Graphics::Model> m_model;
    };
}

#endif //MODEL_ACTOR_CLASS_H
