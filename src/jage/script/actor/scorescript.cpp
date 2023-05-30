#include "jage/script/actor/scorescript.hpp"

using jage::script::actor::ScoreScript;

ScoreScript::ScoreScript(jage::script::abc::ScriptableABC *node)
        : m_score(0)
{
    validate(node);
}

void ScoreScript::onAttach() {

}

void ScoreScript::onSpawn() {

}

void ScoreScript::onUpdate() {

}

void ScoreScript::onDeath() {

}

long ScoreScript::getScore() const {
    return m_score;
}

void ScoreScript::notify(jage::node::actor::DynamicActor *source, const float &delta, const float &current, const float &maximum) {
    m_score += (long)std::round(delta);
    if (current <= 0) {
        m_score += 200;
        onKill.notifyAll(source);
    }
    onScoreUpdate.notifyAll(m_score);
}
