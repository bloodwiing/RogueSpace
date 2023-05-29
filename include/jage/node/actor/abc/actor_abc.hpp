#ifndef JAGE_ACTOR_ABC_HPP
#define JAGE_ACTOR_ABC_HPP

#include <map>
#include <memory>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "jage/graphics/shader.hpp"
#include "jage/tags.hpp"
#include "jage/node/abc/node_abc.hpp"
#include "jage/node/abc/transformable3d_abc.hpp"
#include "jage/node/base/dying_base.hpp"
#include "jage/script/abc/scriptable_abc.hpp"

#define JAGE_ACTOR_ARGS JAGE_NODE_ARGS(jage::node::actor::abc::ActorABC), jage::node::Scene* scene, jage::Tag tag, bool isVolatile

namespace jage::node {
    class Scene;
}

namespace jage::node::actor::abc {

    /// \brief      The main Hierarchy-item base class.
    /// \details    An implementation of a Hierarchy-node system, where every node is an ActorBase and knows references
    ///             to its own parent scene and parent node.
    /// \note       Should not be used raw, but has 2 implementations as a test <b>Scene</b> or <b>Actor</b>
    /// \see        Scene
    /// \see        Actor
    class ActorABC
            : public node::abc::NodeABC<ActorABC>
            , public jage::node::abc::Transformable3DABC
            , public script::abc::ScriptableABC
            , public jage::node::base::DyingBase {
    public:
        template<class T>
        T* addChild(std::string name, Tag tag);
        template<class T, class... Args>
        T* addChild(std::string name, Tag tag, Args&&... args);

        [[nodiscard]] Scene* getScene() const;

        [[nodiscard]] Tag getTag() const;
        [[nodiscard]] bool isVolatile() const;

        [[nodiscard]] virtual glm::vec3 getOrientation() const = 0;
        [[nodiscard]] virtual glm::vec3 getUp() const = 0;

        void setTag(Tag tag);

        void update() override;

        void spawn() override;
        void kill() override;
        void kill(float delay) override;
        bool isDead() const override;

    protected:
        ActorABC(JAGE_ACTOR_ARGS);

        [[nodiscard]] std::string getTypeName() const override;

        Scene* m_scene;

        /// The name of the Hierarchy element
        Tag m_tag = Tag::UNTAGGED;
        const bool m_volatile;

        using node::abc::NodeABC<ActorABC>::addChild;

    private:
        using node::abc::NodeABC<ActorABC>::update;
        using base::DyingBase::updateDeathTimer;
    };
}

#include "actor_abc_impl.tpp"

#endif //JAGE_ACTOR_ABC_HPP
