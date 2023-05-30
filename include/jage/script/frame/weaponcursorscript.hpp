#ifndef JAGE_WEAPON_CURSOR_SCRIPT_HPP
#define JAGE_WEAPON_CURSOR_SCRIPT_HPP

#include "jage/script/abc/script_abc.hpp"
#include "jage/node/frame/spriteframe.hpp"
#include "jage/event/fireevent.hpp"

namespace jage::script::frame {

    class WeaponCursorScript
            : public abc::AttachableScriptABC<node::frame::SpriteFrame>
            , public jage::event::FireEvent
    {
    public:
        WeaponCursorScript(abc::ScriptableABC* node, float add, float duration);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void notify() override;

    private:
        float m_add;
        float m_duration;

        float m_time = 0.0f;
    };
}

#endif //JAGE_WEAPON_CURSOR_SCRIPT_HPP
