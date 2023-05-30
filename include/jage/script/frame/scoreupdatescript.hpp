#ifndef JAGE_SCORE_UPDATE_SCRIPT_HPP
#define JAGE_SCORE_UPDATE_SCRIPT_HPP

#include "jage/script/abc/script_abc.hpp"
#include "jage/node/frame/scoreframe.hpp"
#include "jage/event/scoreupdateevent.hpp"

namespace jage::script::frame {

    class ScoreUpdateScript
            : public abc::AttachableScriptABC<node::frame::ScoreFrame>
            , public jage::event::ScoreUpdateEvent
    {
    public:
        ScoreUpdateScript(abc::ScriptableABC* node);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

        void notify(long score) override;
    };
}

#endif //JAGE_SCORE_UPDATE_SCRIPT_HPP
