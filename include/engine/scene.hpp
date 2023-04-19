#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <vector>

#include "engine/actor/actorbase.hpp"
#include "engine/actor/actor.hpp"

#include "quicklist.hpp"

class Camera;

/// \brief          The main container for every Actor node
/// \details        This is the main or "root" node of every Hierarchy
class Scene : public ActorBase {
public:
    Scene();

    template<class T>
    T* addChild(std::string name);
    template<class T, class... Args>
    T* addChild(std::string name, Args&&... args);

    /// \brief          Creates a new Volatile Child under this Parent Actor
    /// \details        A Volatile Actor list is faster than a Hierarchy, preferred to be used whenever something
    ///                 needs to be spawned and destroyed frequently.
    /// \tparam T       The type of Actor (must be a subclass of <b>ActorBase</b>)
    /// \param name     Name of the Actor node
    /// \return         A pointer to the newly created Actor
    template<class T>
    T* addVolatileChild(std::string name);
    /// \brief          Creates a new Volatile Child under this Parent Actor
    /// \details        A Volatile Actor list is faster than a Hierarchy, preferred to be used whenever something
    ///                 needs to be spawned and destroyed frequently.
    /// \tparam T       The type of Actor (must be a subclass of <b>ActorBase</b>)
    /// \param name     Name of the Actor node
    /// \param args     The list of extra arguments to pass when creating the Actor
    /// \return         A pointer to the newly created Actor
    template<class T, class... Args>
    T* addVolatileChild(std::string name, Args&&... args);

    void update() override;
    void draw(Shader &shader) override;

    /// \return         The flag if Debug Free Flight is enabled
    [[nodiscard]] bool isInFreeFlight() const;

protected:
    [[nodiscard]] std::string getTypeName() const override;

private:
    /// Pre-set name of Scene's Hierarchy name
    static std::string m_hierarchyDisplayName;

    /// QuickList of Volatile Actors
    QuickList<ActorBase*> m_volatileActors;

    // ----- Free Fly toggle -----

    /// A flag that check if Free Fly is enabled
    bool m_freeFly;
    /// The Free Fly Camera
    Camera* m_freeFlyCamera;

    /// Check that stops F2 from calling code more than once during a state change
    bool m_f2Held = false;
    /// The previous Camera that was just unassigned when switched to Free Fly
    Camera* m_prevCamera = nullptr;
};

#include "scene_impl.tpp"

#endif //SCENE_CLASS_H
