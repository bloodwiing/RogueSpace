#ifndef JAGE_MODEL_ACTOR_HPP
#define JAGE_MODEL_ACTOR_HPP

#include "jage/actor/dynamicactor.hpp"
#include "jage/actor/abc/actor_abc.hpp"
#include "jage/runtime/assetstream.hpp"
#include "jage/graphics/model/model.hpp"

namespace jage::actor {

    class ModelActor : public DynamicActor {
    public:
        ModelActor(JAGE_ACTOR_ARGS, const char *fileName, int priority = JAGE_ASSET_STREAM_BASE_PRIORITY);

        void draw(jage::graphics::Shader &shader) override;

    protected:
        [[nodiscard]] std::string getTypeName() const override;

    private:
        std::shared_ptr<jage::graphics::model::Model> m_model;
    };
}

#endif //JAGE_MODEL_ACTOR_HPP
