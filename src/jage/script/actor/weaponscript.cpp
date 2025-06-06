#include "jage/script/actor/weaponscript.hpp"

#include "jage/node/actor/physicsactor.hpp"
#include "jage/node/actor/modelactor.hpp"
#include "jage/runtime/time.hpp"
#include "jage/script/actor/bulletscript.hpp"

using jage::script::actor::WeaponScript;

WeaponScript::WeaponScript(abc::ScriptableABC* node, float bulletSpeed, Tag bulletTargetTag, float bulletDamage)
    : m_bulletSpeed(bulletSpeed)
    , m_bulletTargetTag(bulletTargetTag)
    , m_bulletDamage(bulletDamage)
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

void WeaponScript::shootThisFrame(const glm::vec3& extraVelocity, const glm::vec3& orientation, const glm::vec3& up) {
    if (m_fireCoolDown > 0.0f)
        return;

    // relative vectors
    const auto right = glm::cross(orientation, up);

    // Actor
    auto bullet = m_node->getScene()->addVolatileChild<node::actor::PhysicsActor>("Bullet", Tag::BULLET, 0.0f, 0.0f);
    bullet->addChild<node::actor::ModelActor>("model", Tag::MESH, "./res/model/trailblazer/bullet/BulletTemp.gltf");
    bullet->attachScript<BulletScript>(m_bulletTargetTag, 1.0f, m_bulletDamage);

    // Translate to world position
    glm::vec3 spawnOffset = (m_fireFromLeft ? -right : right) * 0.35f + up * -0.15f;
    bullet->setTranslation(m_node->getWorldPosition() + spawnOffset);

    // Launch it
    bullet->setRotation(glm::quatLookAt((glm::vec3)glm::vec4(orientation, 0.0), up));
    bullet->addForce((glm::vec3)glm::vec4(orientation, 0.0) * m_bulletSpeed + extraVelocity);
    bullet->kill(10.0f);

    // Remember for next projectile
    m_fireCoolDown = 0.1f;
    m_fireFromLeft = !m_fireFromLeft;

    onFire.notifyAll();
}

void WeaponScript::shootThisFrame(const glm::vec3 &extraVelocity) {
    shootThisFrame(extraVelocity, m_node->getOrientation(), m_node->getUp());
}

float WeaponScript::getBulletSpeed() const {
    return m_bulletSpeed;
}

void WeaponScript::setBulletSpeed(float bulletSpeed) {
    m_bulletSpeed = bulletSpeed;
}
