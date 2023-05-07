#ifndef JAGE_DYNAMIC_ACTOR_HPP
#define JAGE_DYNAMIC_ACTOR_HPP

#include "jage/actor/staticactor.hpp"
#include "jage/actor/abc/actor_abc.hpp"
#include "jage/actor/scene.hpp"

namespace jage::actor {
    /// \brief          A Transformable subclass of Actor.
    /// \details        This Actor is able to be Translated, Rotated and Scaled.
    ///                 Any transformation will mark itself and its children for a Matrix update
    class DynamicActor : public StaticActor {
    public:
        /// \note           Should not be used raw, please use addChild
        /// \param scene    Containing Scene of the Actor node
        /// \param parent   Parent of the Actor node
        /// \param name     Name of the Actor node
        /// \see            Scene#addChild
        /// \see            Actor#addChild
        DynamicActor(Scene* scene, abc::ActorABC* parent, std::string name);

        void update() override;

        [[nodiscard]] glm::vec3 getTranslation() const override;
        [[nodiscard]] glm::quat getRotation() const override;
        [[nodiscard]] glm::vec3 getScale() const override;
        [[nodiscard]] glm::vec3 getOrientation() const override;
        [[nodiscard]] glm::vec3 getUp() const override;

        [[nodiscard]] glm::mat4 getWorldMatrix() const override;

        void setTranslation(const glm::vec3& tra) override;
        void setRotation(const glm::quat& rot) override;
        void setScale(const glm::vec3& sca) override;
        /// \brief          A function to disassemble a <u>relative</u> Transformation matrix and
        ///                 apply its individual components.
        /// \param mat      The Relative Transformation Matrix to process
        void setMatrix(const glm::mat4& mat);

        /// \brief          A helper function to offset the current Translation with the given vector.
        /// \details        The provided value is added onto the current Translation of the Actor
        ///                 and then it is marked for a Matrix update.
        /// \param tra      The Translation change
        void translate(const glm::vec3& tra);
        /// \brief          A helper function to offset the current Rotation with the given vector.
        /// \details        The provided value is multiplied with the current Rotation of the Actor
        ///                 and then it is marked for a Matrix update.
        /// \param rot      The Rotation change
        void rotate(const glm::quat& rot);
        /// \brief          A helper function to offset the current Scale with the given vector.
        /// \details        The provided value is multiplied with the current Scale of the Actor
        ///                 and then it is marked for a Matrix update.
        /// \param sca      The Scale change
        void scale(const glm::vec3& sca);

        /// \brief          Marks the element as pending for a Matrix recalculation.
        void flagForMatrixUpdate();
        void flagForVectorUpdate();

    protected:
        [[nodiscard]] std::string getTypeName() const override;

    private:
        /// The relative Translation of the Actor
        glm::vec3 m_translation = glm::vec3(0.0f);
        /// The relative Rotation of the Actor
        glm::quat m_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        /// The relative Scale of the Actor
        glm::vec3 m_scale = glm::vec3(1.0f);
        glm::vec3 m_orientation = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);

        /// The calculated and cached Matrix after being applied from Parent and relative Transformations
        glm::mat4 m_worldMatrix = glm::mat4(1.0f);

        /// Marks that m_worldMatrix needs a recalculation during the next ActorBase#update
        bool m_needsMatrixUpdate = false;
        bool m_needsVectorUpdate = false;
    };
}

#endif //JAGE_DYNAMIC_ACTOR_HPP
