#include "jage/script/frame/scoreupdatescript.hpp"

using jage::script::frame::ScoreUpdateScript;

ScoreUpdateScript::ScoreUpdateScript(jage::script::abc::ScriptableABC *node) {
    validate(node);
}

void ScoreUpdateScript::onAttach() {

}

void ScoreUpdateScript::onSpawn() {

}

void ScoreUpdateScript::onUpdate() {

}

void ScoreUpdateScript::onDeath() {

}

void ScoreUpdateScript::notify(long score) {
    m_node->setScore(score);
}
