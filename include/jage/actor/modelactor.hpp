#ifndef MODEL_ACTOR_CLASS_H
#define MODEL_ACTOR_CLASS_H

#include "jage/actor/dynamicactor.hpp"
#include "jage/actor/abc/actor_abc.hpp"
#include "jage/runtime/assetstream.hpp"
#include "jage/graphics/model/model.hpp"

namespace jage::actor {

    class ModelActor : public DynamicActor {
    public:
        ModelActor(Scene *scene, abc::ActorABC *parent, std::string name, const char *fileName, int priority = ASSET_STREAM_BASE_PRIORITY);

        void draw(jage::graphics::Shader &shader) override;

    protected:
        [[nodiscard]] std::string getTypeName() const override;

    private:
        std::shared_ptr<jage::graphics::model::Model> m_model;
    };
}

#endif //MODEL_ACTOR_CLASS_H
