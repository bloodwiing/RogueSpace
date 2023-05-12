#ifndef JAGE_PHYSICS_ACTOR_HPP
#define JAGE_PHYSICS_ACTOR_HPP

#include <glm/glm.hpp>

#include "jage/actor/dynamicactor.hpp"
#include "jage/actor/abc/actor_abc.hpp"

namespace jage::actor {

    /// \brief          A Velocity-based subclass of DynamicActor.
    /// \details        This Actor can move on its own, have both linear and angular velocity and slow down over time
    class PhysicsActor : public DynamicActor {
    public:
        /// \note           Should not be used raw, please use addChild
        /// \param scene    Containing Scene of the Actor node
        /// \param parent   Parent of the Actor node
        /// \param name     Name of the Actor node
        /// \param weight   The influence of how fast the Actor slows its linear velocity down
        /// \param drag     The influence of how fast the Actor slows its angular velocity down
        /// \see            Scene#addChild
        /// \see            Actor#addChild
        PhysicsActor(Scene* scene, abc::ActorABC* parent, std::string name, Tag tag, bool isVolatile, float weight, float drag);

        void update() override;

        /// \return         The current Weight of the Actor
        [[nodiscard]] float getWeight() const;
        /// \return         The current Drag of the Actor
        [[nodiscard]] float getDrag() const;
        /// \return         The current linear Velocity direction vector of the Actor
        [[nodiscard]] glm::vec3 getLinearVelocity() const;
        /// \return         The current Angular Velocity Euler angle of the Actor
        [[nodiscard]] glm::vec3 getAngularVelocity() const;

        /// \brief          Sets a new Weight of the Actor
        void setWeight(float weight);
        /// \brief          Sets a new Drag of the Actor
        void setDrag(float drag);
        /// \brief          Forces the Actor to suddenly use this Linear Velocity
        /// \note           It's often better to add Force instead of setting it
        /// \param linear   The new Linear Velocity
        /// \see            PhysicsActor#addForce
        void setLinearVelocity(const glm::vec3& linear);
        /// \brief          Forces the Actor to suddenly use this Angular Velocity
        /// \note           It's often better to add Torque instead of setting it
        /// \param angular  The new Angular Velocity
        /// \see            PhysicsActor#addTorque
        void setAngularVelocity(const glm::vec3& angular);

        /// \brief          Pushes the object in the specified direction with the power of the length of direction
        /// \param force    The direction to push the object in
        void addForce(glm::vec3 force);
        /// \brief          Spins the object in the specified Euler angle with the power of the length of the Euler angle
        /// \param torque   The Euler angle to spin the object in
        void addTorque(glm::vec3 torque);

        /// \brief              Applies linear velocity to a Dynamic Actor for the Delta frame
        /// \details            Can be applied to any DynamicActor, but it is recommended to use PhysicsActor as it
        ///                     automatically handles velocity and stores it.
        /// \param target[in]   The target Actor to apply the change to
        /// \param linear[in]   The Translational or Linear velocity
        /// \return             - true, if change was applied
        ///                     - false, if no change happened
        static bool applyLinearVelocity(DynamicActor* target, const glm::vec3& linear);
        /// \brief              Applies angular velocity to a Dynamic Actor for the Delta frame
        /// \details            Can be applied to any DynamicActor, but it is recommended to use PhysicsActor as it
        ///                     automatically handles velocity and stores it.
        /// \param target[in]   The target Actor to apply the change to
        /// \param angular[in]  The Rotational or Angular velocity
        /// \return             - true, if change was applied
        ///                     - false, if no change happened
        static bool applyAngularVelocity(DynamicActor* target, const glm::vec3& angular);

        /// \brief                  Shrinks the velocity vector for the current Delta frame
        /// \param vector[in,out]   The vector reference to shrink
        /// \param influence        The speed that the vector diminishes at
        /// \param deadZone         The minimum size requirement for the vector, otherwise sets it to zero
        static void diminishVelocity(glm::vec3& vector, float influence, float deadZone);

        /// \brief              Helpful function to check if a vector has been zeroed out
        /// \param vector[in]   The vector to check
        /// \return             - true, if vector is zero
        ///                     - false, if vector is not zero
        [[nodiscard]] static bool isVectorZero(const glm::vec3& vector);

    protected:
        [[nodiscard]] std::string getTypeName() const override;

    private:
        /// The current Weight of the PhysicsActor
        float m_weight;
        /// The current Drag of the PhysicsActor
        float m_drag;

        /// The current Linear Velocity of the PhysicsActor
        glm::vec3 m_linearVelocity;
        /// The current Angular Velocity of the PhysicsActor
        glm::vec3 m_angularVelocity;
    };
}

#endif //JAGE_PHYSICS_ACTOR_CLASS_H
