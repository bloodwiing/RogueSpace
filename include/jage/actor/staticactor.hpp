#ifndef JAGE_STATIC_ACTOR_HPP
#define JAGE_STATIC_ACTOR_HPP

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "jage/actor/abc/actor_abc.hpp"
#include "jage/script/abc/script_abc.hpp"

namespace jage::actor {

    /// \brief          Main world object type.
    /// \details        This Actor can exist in the world but is static in Transformation and is able to die
    class StaticActor : public abc::ActorABC {
    public:
        /// \note           Should not be used raw, please use addChild
        /// \param scene    Containing Scene of the Actor node
        /// \param parent   Parent of the Actor node
        /// \param name     Name of the Actor node
        /// \see            Scene#addChild
        /// \see            Actor#addChild
        StaticActor(Scene* scene, abc::ActorABC* parent, std::string name, Tag tag, bool isVolatile);

        /// \brief          Creates a new Child under this Parent Actor
        /// \tparam T       The type of Actor (must be a subclass of <b>ActorBase</b>)
        /// \param name     Name of the Actor node
        /// \return         A pointer to the newly created Actor
        template<class T>
        T* addChild(std::string name, Tag tag);
        /// \brief          Creates a new Child under this Parent Actor
        /// \tparam T       The type of Actor (must be a subclass of <b>ActorBase</b>)
        /// \param name     Name of the Actor node
        /// \param args     The list of extra arguments to pass when creating the Actor
        /// \return         A pointer to the newly created Actor
        template<class T, class... Args>
        T* addChild(std::string name, Tag tag, Args&&... args);

        template<class T>
        T* attachScript();
        template<class T, class... Args>
        T* attachScript(Args&&... args);

        template<class T>
        T* findScript();

        /// \returns        The containing Scene
        [[nodiscard]] Scene* getScene() const;

        /// \return         The relative Translation
        [[nodiscard]] glm::vec3 getTranslation() const override;
        /// \return         The relative Rotation
        [[nodiscard]] glm::quat getRotation() const override;
        /// \return         The relative Scale
        [[nodiscard]] glm::vec3 getScale() const override;
        [[nodiscard]] glm::vec3 getOrientation() const override;
        [[nodiscard]] glm::vec3 getUp() const override;
        [[nodiscard]] glm::vec3 getWorldPosition() const override;
        [[nodiscard]] bool isDead() const override;

        /// \brief          Sets the relative Translation of the object
        /// \note           Only implemented in <b>DynamicActor</b>
        /// \param tra      New Translation
        void setTranslation(const glm::vec3& tra) override {};
        /// \brief          Sets the relative Rotation of the object
        /// \note           Only implemented in <b>DynamicActor</b>
        /// \param rot      New Rotation
        void setRotation(const glm::quat& rot) override {};
        /// \brief          Sets the relative Scale of the object
        /// \note           Only implemented in <b>DynamicActor</b>
        /// \param sca      New Scale
        void setScale(const glm::vec3& sca) override {};
        /// \brief          Marks the Actor as Dead
        /// \details        A Dead Actor is marked for removal during the soonest possible update event of a parent Actor
        /// \param wait     An optional parameter to delay the removal of the Actor.
        ///                 A value of -1.0 will mark the Actor instantly without delay
        void markDead(float wait = -1.0f);

        void update() override;
        void draw(jage::graphics::Shader &shader) override;

    protected:
        [[nodiscard]] std::string getTypeName() const override;

        /// The containing Scene
        Scene* m_scene;

        /// A timer that tracks how much longer does the Actor have to live until it gets marked as Dead
        float m_deathTimer = -1.0f;
        /// A death flag
        /// \see        Actor#markDead
        bool m_dead = false;

        /// A list of attachable Scripts
        std::vector<std::shared_ptr<jage::script::abc::ScriptABC>> m_scripts;
    };
}

#include "staticactor_impl.tpp"

#endif //JAGE_STATIC_ACTOR_HPP
