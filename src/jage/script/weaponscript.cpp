#include "jage/script/weaponscript.hpp"

#include "jage/actor/physicsactor.hpp"
#include "jage/actor/modelactor.hpp"
#include "jage/runtime/time.hpp"
#include "jage/script/colliderscript.hpp"

using jage::script::WeaponScript;

WeaponScript::WeaponScript(jage::actor::abc::ActorABC *node, float bulletSpeed, Tag bulletTargetTag)
    : m_bulletSpeed(bulletSpeed)
    , m_bulletTargetTag(bulletTargetTag)
{
    validate(node);
}

void WeaponScript::onAttach() {

}

void WeaponScript::onSpawn() {

}

void WeaponScript::onUpdate() {
    using jage::runtime::Time;

    // Weapon cool down
    if (m_fireCoolDown > 0.0f)
        m_fireCoolDown -= Time::getDeltaFloat();
}

void WeaponScript::onDeath() {

}

void jage::script::WeaponScript::shootThisFrame(const glm::vec3 &extraVelocity) {
    if (m_fireCoolDown > 0.0f)
        return;

    // relative vectors
    const auto& orientation = m_node->getOrientation();
    const auto& up = m_node->getUp();
    const auto right = glm::cross(orientation, up);

    // Actor
    auto bullet = m_node->getScene()->addVolatileChild<jage::actor::PhysicsActor>("Bullet", Tag::BULLET, 0.0f, 0.0f);
    bullet->addChild<jage::actor::ModelActor>("model", Tag::MESH, "./res/bullet/BulletTemp.gltf");
    bullet->attachScript<script::ColliderScript>(m_bulletTargetTag, 1.0f);

    // Translate to world position
    glm::vec3 offset = (m_fireFromLeft ? -right : right) * 0.35f + up * -0.15f;
    bullet->setTranslation(m_node->getWorldPosition() + offset);

    // Launch it
    bullet->setRotation(glm::quatLookAt((glm::vec3)glm::vec4(orientation, 0.0), up));
    bullet->addForce((glm::vec3)glm::vec4(orientation, 0.0) * m_bulletSpeed + extraVelocity);
    bullet->markDead(10.0f);

    // Remember for next projectile
    m_fireCoolDown = 0.1f;
    m_fireFromLeft = !m_fireFromLeft;
}

float jage::script::WeaponScript::getBulletSpeed() const {
    return m_bulletSpeed;
}

void jage::script::WeaponScript::setBulletSpeed(float bulletSpeed) {
    m_bulletSpeed = bulletSpeed;
}
