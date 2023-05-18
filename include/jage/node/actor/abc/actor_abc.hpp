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
    class ActorABC : public node::abc::NodeABC<ActorABC> {
    protected:
        ActorABC(JAGE_ACTOR_ARGS);

        void tagToScene(Scene* scene);
    public:
        [[nodiscard]] std::map<std::string, ChildEntry> getChildren() const;
        [[nodiscard]] ActorABC* getChild(const std::string& name) const;

        template<class T>
        T* addChild(JAGE_ACTOR_ARGS);
        template<class T, class... Args>
        T* addChild(JAGE_ACTOR_ARGS, Args&&... args);

        /// \returns        Possible values:
        ///                 - #ActorABC
        ///                 - nullptr
        [[nodiscard]] ActorABC* getParent() const;

        /// \returns        The name of the current Hierarchy element
        [[nodiscard]] std::string getName() const;
        [[nodiscard]] Tag getTag() const;
        [[nodiscard]] bool isVolatile() const;

        /// \return         The calculated Transformation matrix after applying all parent transformations
        [[nodiscard]] virtual glm::mat4 getWorldMatrix() const;

        /// \return         The relative Translation
        [[nodiscard]] virtual glm::vec3 getTranslation() const = 0;
        /// \return         The relative Rotation
        [[nodiscard]] virtual glm::quat getRotation() const = 0;
        /// \return         The relative Scale
        [[nodiscard]] virtual glm::vec3 getScale() const = 0;
        /// \return         A conditional check whether the Actor should be removed from the Hierarchy during the next update
        [[nodiscard]] virtual glm::vec3 getOrientation() const = 0;
        [[nodiscard]] virtual glm::vec3 getUp() const = 0;
        [[nodiscard]] virtual glm::vec3 getWorldPosition() const = 0;
        [[nodiscard]] virtual bool isDead() const;

        void setTag(Tag tag);

        /// \brief          Sets the relative Translation of the object
        /// \note           Only implemented in <b>DynamicActor</b>
        /// \param tra      New Translation
        virtual void setTranslation(const glm::vec3& tra) = 0;
        /// \brief          Sets the relative Rotation of the object
        /// \note           Only implemented in <b>DynamicActor</b>
        /// \param rot      New Rotation
        virtual void setRotation(const glm::quat& rot) = 0;
        /// \brief          Sets the relative Scale of the object
        /// \note           Only implemented in <b>DynamicActor</b>
        /// \param sca      New Scale
        virtual void setScale(const glm::vec3& sca) = 0;

    protected:
        [[nodiscard]] std::string getTypeName() const override;

        /// The name of the Hierarchy element
        Tag m_tag = Tag::UNTAGGED;
        const bool m_volatile;

    private:
        using node::abc::NodeABC<ActorABC>::addChild;
    };
}

#include "actor_abc_impl.tpp"

#endif //JAGE_ACTOR_ABC_HPP
