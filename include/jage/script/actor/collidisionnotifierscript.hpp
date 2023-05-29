#ifndef JAGE_COLLIDER_SCRIPT_HPP
#define JAGE_COLLIDER_SCRIPT_HPP

#include "jage/node/actor/dynamicactor.hpp"
#include "jage/script/abc/script_abc.hpp"

namespace jage::script::actor {

    class CollisionNotifierScript : public abc::AttachableScriptABC<jage::node::actor::DynamicActor> {
    public:
        CollisionNotifierScript(abc::ScriptableABC* node, Tag tagFilter, float radius);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        [[nodiscard]] Tag getTagFilter() const;
        void setTagFilter(Tag tag);

        [[nodiscard]] float getRadius() const;
        void setRadius(float radius);

    private:
        Tag m_tagFilter;

        float m_radius;
    };
}

#endif //JAGE_COLLIDER_SCRIPT_HPP
