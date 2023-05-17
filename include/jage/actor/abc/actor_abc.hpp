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

namespace jage::actor {
    class Scene;
}

namespace jage::actor::abc {

    /// \brief      The main Hierarchy-item base class.
    /// \details    An implementation of a Hierarchy-node system, where every node is an ActorBase and knows references
    ///             to its own parent scene and parent node.
    /// \note       Should not be used raw, but has 2 implementations as a test <b>Scene</b> or <b>Actor</b>
    /// \see        Scene
    /// \see        Actor
    class ActorABC : public node::abc::NodeABC<ActorABC> {
    protected:

        /// \note           Should not be used raw, please use addChild
        /// \param parent   Parent of the Actor node
        /// \param name     Name of the Actor node
        /// \see            Scene#addChild
        /// \see            Actor#addChild
        ActorABC(ActorABC* parent, std::string& name, Tag tag, bool isVolatile);

        void tagToScene(Scene* scene);
    public:
        [[nodiscard]] std::map<std::string, ChildEntry> getChildren() const;
        [[nodiscard]] ActorABC* getChild(const std::string& name) const;

        template<class T>
        T* addChild(ActorABC* parent, std::string& name, Tag tag, bool isVolatile);
        template<class T, class... Args>
        T* addChild(ActorABC* parent, std::string& name, Tag tag, bool isVolatile, Args&&... args);

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

        /// \brief          Hierarchy element update event, runs every frame
        /// \note           Runs before every draw event
        virtual void update();

        /// \brief          Hierarchy element draw event, runs every frame
        /// \note           Runs after every update event
        virtual void draw(jage::graphics::Shader& shader);

        /// \brief          Creates a Human-readable text visualisation of the Hierarchy
        ///                 (current element being the root node of reference)
        /// \param indent   Optional indentation offset, please keep blank for best appearance
        /// \return         Generated Hierarchy representation
        [[nodiscard]] std::string toHierarchyString(uint16_t indent = 0) const;

    protected:
        [[nodiscard]] std::string getTypeName() const override;

        /// The name of the Hierarchy element
        Tag m_tag = Tag::UNTAGGED;
        const bool m_volatile;
        /// Hierarchy element's map of children
        std::map<std::string, ChildEntry> m_children;
        /// The pointer of the Hierarchy element's parent
        ActorABC* m_parent;

    private:
        /// \brief          Internal function. Registers the created actor to the map of children.
        /// \details        Keep checking if the name is taken, if it is, it will increment the entry with the same name
        ///                 and will attempt to insert the child with an altered name that has a number appended to it.<br>
        ///                 This is recursive until an empty slot is found.
        /// \tparam T       The type of Actor (must be a subclass of <b>ActorBase</b>)
        /// \return         A pointer to the newly created Actor
        template<class T>
        void internalRegisterChild(std::shared_ptr<T> child);

        ActorABC(const ActorABC&);
        ActorABC& operator=(const ActorABC&);
    };
}

std::ostream& operator<<(std::ostream& stream, jage::actor::abc::ActorABC* actor);

#include "actor_abc_impl.tpp"

#endif //JAGE_ACTOR_ABC_HPP
