#ifndef JAGE_SCENE_HPP
#define JAGE_SCENE_HPP

#include <vector>

#include "jage/actor/staticactor.hpp"
#include "jage/actor/abc/actor_abc.hpp"

#include "quicklist.hpp"

namespace jage::actor {

    class Camera;

    /// \brief          The main container for every Actor node
    /// \details        This is the main or "root" node of every Hierarchy
    class Scene : public abc::ActorABC {
    public:
        Scene();

        template<class T>
        T* addChild(std::string name, Tag tag);
        template<class T, class... Args>
        T* addChild(std::string name, Tag tag, Args&&... args);

        /// \brief          Returns the QuickList of Volatile Actors
        [[nodiscard]] Utility::QuickList<std::shared_ptr<abc::ActorABC>> getVolatileChildren() const;

        /// \brief          Creates a new Volatile Child under this Parent Actor
        /// \details        A Volatile Actor list is faster than a Hierarchy, preferred to be used whenever something
        ///                 needs to be spawned and destroyed frequently.
        /// \tparam T       The type of Actor (must be a subclass of <b>ActorBase</b>)
        /// \param name     Name of the Actor node
        /// \return         A pointer to the newly created Actor
        template<class T>
        T* addVolatileChild(std::string name, Tag tag);
        /// \brief          Creates a new Volatile Child under this Parent Actor
        /// \details        A Volatile Actor list is faster than a Hierarchy, preferred to be used whenever something
        ///                 needs to be spawned and destroyed frequently.
        /// \tparam T       The type of Actor (must be a subclass of <b>ActorBase</b>)
        /// \param name     Name of the Actor node
        /// \param args     The list of extra arguments to pass when creating the Actor
        /// \return         A pointer to the newly created Actor
        template<class T, class... Args>
        T* addVolatileChild(std::string name, Tag tag, Args&&... args);

        void tagActorToMap(const std::shared_ptr<abc::ActorABC>& actor);

        [[nodiscard]] glm::vec3 getTranslation() const override;
        [[nodiscard]] glm::quat getRotation() const override;
        [[nodiscard]] glm::vec3 getScale() const override;
        [[nodiscard]] glm::vec3 getOrientation() const override;
        [[nodiscard]] glm::vec3 getUp() const override;
        [[nodiscard]] glm::vec3 getWorldPosition() const override;

        void setTranslation(const glm::vec3 &tra) override {};
        void setRotation(const glm::quat &rot) override {};
        void setScale(const glm::vec3 &sca) override {};

        void update() override;
        void draw(jage::graphics::Shader &shader) override;

    protected:
        [[nodiscard]] std::string getTypeName() const override;

    private:
        /// Pre-set name of Scene's Hierarchy name
        static std::string m_hierarchyDisplayName;

        /// QuickList of Volatile Actors
        Utility::QuickList<std::shared_ptr<abc::ActorABC>> m_volatileActors;

        std::vector<std::vector<std::weak_ptr<abc::ActorABC>>> m_taggedMap;
    };
}

#include "scene_impl.tpp"

#endif //JAGE_SCENE_HPP
