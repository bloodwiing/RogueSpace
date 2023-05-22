#ifndef JAGE_STATIC_ACTOR_HPP
#define JAGE_STATIC_ACTOR_HPP

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "jage/node/actor/abc/actor_abc.hpp"

namespace jage::node::actor {

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
        StaticActor(JAGE_ACTOR_ARGS);

        /// \return         The relative Translation
        [[nodiscard]] glm::vec3 getTranslation() const override;
        /// \return         The relative Rotation
        [[nodiscard]] glm::quat getRotation() const override;
        /// \return         The relative Scale
        [[nodiscard]] glm::vec3 getScale() const override;
        [[nodiscard]] glm::vec3 getOrientation() const override;
        [[nodiscard]] glm::vec3 getUp() const override;
        [[nodiscard]] glm::vec3 getWorldPosition() const override;

        void setWorldMatrix(const glm::mat4 &mat) override {};
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

        using jage::node::actor::abc::ActorABC::update;
        void draw(jage::graphics::Shader &shader) override;

    protected:
        [[nodiscard]] std::string getTypeName() const override;
    };
}

#endif //JAGE_STATIC_ACTOR_HPP
