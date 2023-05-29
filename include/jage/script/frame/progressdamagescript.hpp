#ifndef JAGE_PROGRESS_DAMAGE_SCRIPT
#define JAGE_PROGRESS_DAMAGE_SCRIPT

#include "jage/script/abc/script_abc.hpp"
#include "jage/node/frame/progressbarframe.hpp"
#include "jage/event/damageevent.hpp"

namespace jage::script::frame {

    class ProgressDamageScript
            : public abc::AttachableScriptABC<node::frame::ProgressBarFrame>
            , public event::DamageEvent
    {
    public:
        ProgressDamageScript(jage::script::abc::ScriptableABC* node);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void notify(const float& delta, const float& current, const float& max) override;
    };
}

#endif //JAGE_PROGRESS_DAMAGE_SCRIPT
