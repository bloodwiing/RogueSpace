#ifndef JAGE_NOTIFICATION_KILL_SCRIPT_HPP
#define JAGE_NOTIFICATION_KILL_SCRIPT_HPP

#include "jage/script/abc/script_abc.hpp"
#include "jage/node/frame/spriteframe.hpp"
#include "jage/event/killevent.hpp"

namespace jage::script::frame {

    class NotificationKillScript
            : public abc::AttachableScriptABC<node::frame::SpriteFrame>
            , public jage::event::KillEvent
    {
    public:
        NotificationKillScript(abc::ScriptableABC* node, float appearTime, float stayTime, float removeTime);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void notify(node::actor::DynamicActor* source) override;

    private:
        float m_appearTime;
        float m_stayTime;
        float m_removeTime;

        float m_time = 0.0f;

        int m_count = 0;
    };
}

#endif //JAGE_NOTIFICATION_KILL_SCRIPT_HPP
