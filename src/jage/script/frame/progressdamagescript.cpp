#include "jage/script/frame/progressdamagescript.hpp"

using jage::script::frame::ProgressDamageScript;

ProgressDamageScript::ProgressDamageScript(jage::script::abc::ScriptableABC* node) {
    validate(node);
}

void ProgressDamageScript::onAttach() {

}

void ProgressDamageScript::onSpawn() {

}

void ProgressDamageScript::onUpdate() {

}

void ProgressDamageScript::onDeath() {

}

void ProgressDamageScript::notify(const float& delta, const float& current, const float& max) {
    m_node->setProgress(current / max);
}
