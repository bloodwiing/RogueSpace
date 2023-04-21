#ifndef ACTOR_BASE_CLASS_H
#define ACTOR_BASE_CLASS_H

#include <map>
#include <memory>

#define GLFW_INCLUDE_NONE
#include <glfw3.h>

#include "glm/glm.hpp"

#include "graphics/shader.hpp"

class Scene;

/// \brief      The main Hierarchy-item base class.
/// \details    An implementation of a Hierarchy-node system, where every node is an ActorBase and knows references
///             to its own parent scene and parent node.
/// \note       Should not be used raw, but has 2 implementations as a test <b>Scene</b> or <b>Actor</b>
/// \see        Scene
/// \see        Actor
class ActorBase {
protected:
    /// \brief          A container that remembers how many times a name has been reused for a child
    struct ChildEntry {
        std::shared_ptr<ActorBase> value;
        uint16_t nameRepeat;
    };

    /// \note           Should not be used raw, please use addChild
    /// \param scene    Containing Scene of the Actor node
    /// \param parent   Parent of the Actor node
    /// \param name     Name of the Actor node
    /// \see            Scene#addChild
    /// \see            Actor#addChild
    ActorBase(Scene* scene, ActorBase* parent, std::string& name);
public:
    /// \brief          Returns the map of Actor name and Actor entry pairs
    [[nodiscard]] std::map<std::string, ChildEntry> getChildren() const;
    /// \brief          Returns a pointer to a child Actor of the current Hierarchy element
    /// \param name     The name of the child to search for
    /// \returns        Possible values:
    ///                 - #ActorBase*
    ///                 - nullptr
    [[nodiscard]] ActorBase* getChild(const std::string& name) const;

    /// \brief          Creates a new Child under this Hierarchy element
    /// \note           Should not be used raw, please use addChild
    /// \tparam T       The type of Actor (must be a subclass of <b>ActorBase</b>)
    /// \param scene    Containing Scene of the Actor node
    /// \param parent   Parent of the Actor node
    /// \param name     Name of the Actor node
    /// \return         A pointer to the newly created Actor
    /// \see            Scene#addChild
    /// \see            Actor#addChild
    template<class T>
    T* addChild(Scene* scene, ActorBase* parent, std::string& name);

    /// \brief          Creates a new Child under this Hierarchy element
    /// \note           Should not be used raw, please use addChild
    /// \tparam T       The type of Actor (must be a subclass of <b>ActorBase</b>)
    /// \param scene    Containing Scene of the Actor node
    /// \param parent   Parent of the Actor node
    /// \param name     Name of the Actor node
    /// \param args     The list of extra arguments to pass when creating the Actor
    /// \return         A pointer to the newly created Actor
    /// \see            Scene#addChild
    /// \see            Actor#addChild
    template<class T, class... Args>
    T* addChild(Scene* scene, ActorBase* parent, std::string& name, Args&&... args);

    /// \returns        Possible values:
    ///                 - #ActorBase
    ///                 - nullptr
    [[nodiscard]] ActorBase* getParent() const;

    /// \returns        The name of the current Hierarchy element
    [[nodiscard]] std::string getName() const;

    /// \return         The calculated Transformation matrix after applying all parent transformations
    [[nodiscard]] virtual glm::mat4 getWorldMatrix() const;

    /// \return         A conditional check whether the Actor should be removed from the Hierarchy during the next update
    [[nodiscard]] virtual bool isDead() const;

    /// \brief          Hierarchy element update event, runs every frame
    /// \note           Runs before every draw event
    virtual void update();

    /// \brief          Hierarchy element draw event, runs every frame
    /// \note           Runs after every update event
    virtual void draw(Shader& shader);

    /// \brief          Creates a Human-readable text visualisation of the Hierarchy
    ///                 (current element being the root node of reference)
    /// \param indent   Optional indentation offset, please keep blank for best appearance
    /// \return         Generated Hierarchy representation
    [[nodiscard]] std::string toHierarchyString(uint16_t indent = 0) const;

protected:
    /// \returns        Returns its own Hierarchy element type name
    [[nodiscard]] virtual std::string getTypeName() const;

    /// The name of the Hierarchy element
    std::string m_name;
    /// Hierarchy element's map of children
    std::map<std::string, ChildEntry> m_children;
    /// The pointer of the Hierarchy element's parent
    ActorBase* m_parent;

private:
    /// \brief          Internal function. Registers the created actor to the map of children.
    /// \details        Keep checking if the name is taken, if it is, it will increment the entry with the same name
    ///                 and will attempt to insert the child with an altered name that has a number appended to it.<br>
    ///                 This is recursive until an empty slot is found.
    /// \tparam T       The type of Actor (must be a subclass of <b>ActorBase</b>)
    /// \return         A pointer to the newly created Actor
    template<class T>
    void internalRegisterChild(std::shared_ptr<T> child);
};

std::ostream& operator<<(std::ostream& stream, ActorBase* actor);

#include "actorbase_impl.tpp"

#endif //ACTOR_BASE_CLASS_H
