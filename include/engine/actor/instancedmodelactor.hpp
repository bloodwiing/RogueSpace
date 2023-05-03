#ifndef INSTANCED_MODEL_ACTOR_CLASS_H
#define INSTANCED_MODEL_ACTOR_CLASS_H

#include "./modelactor.hpp"

namespace Engine::Actors {

    class InstancedModelActor : public ModelActor {
    public:
        InstancedModelActor(Scene *scene, ActorBase *parent, std::string name, const char *fileName, int priority = ASSET_STREAM_BASE_PRIORITY);

        void draw(Graphics::Shader &shader) override;

    protected:
        [[nodiscard]] std::string getTypeName() const override;
    };
}

#endif //INSTANCED_MODEL_ACTOR_CLASS_H
