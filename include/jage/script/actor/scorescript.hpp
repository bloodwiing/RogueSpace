#ifndef JAGE_SCORE_SCRIPT_HPP
#define JAGE_SCORE_SCRIPT_HPP

#include "jage/script/abc/script_abc.hpp"
#include "jage/node/actor/dynamicactor.hpp"
#include "jage/event/damageevent.hpp"
#include "jage/event/scoreupdateevent.hpp"
#include "jage/event/killevent.hpp"

namespace jage::script::actor {

    class ScoreScript
            : public abc::AttachableScriptABC<node::actor::DynamicActor>
            , public jage::event::DamageEvent
    {
    public:
        ScoreScript(abc::ScriptableABC* node);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        [[nodiscard]] long getScore() const;

        void notify(node::actor::DynamicActor* source, const float& delta, const float& current, const float& maximum) override;

        event::ScoreUpdateEvent::Manager onScoreUpdate;
        event::KillEvent::Manager onKill;

    private:
        long m_score;
    };
}

#endif //JAGE_SCORE_SCRIPT_HPP
