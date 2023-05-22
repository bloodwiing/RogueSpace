#include "jage/script/abc/scriptable_abc.hpp"

using jage::script::abc::ScriptableABC;

void ScriptableABC::update() {
    for (auto& script : m_scripts) {
        script->onUpdate();
        if (isDead())
            script->onDeath();
    }
}
