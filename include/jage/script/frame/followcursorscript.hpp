#ifndef JAGE_FOLLOW_CURSOR_SCRIPT_HPP
#define JAGE_FOLLOW_CURSOR_SCRIPT_HPP

#include "jage/script/abc/script_abc.hpp"
#include "jage/node/frame/basicframe.hpp"

namespace jage::script::frame {

    class FollowCursorScript
            : public abc::AttachableScriptABC<jage::node::frame::BasicFrame>
    {
    public:
        FollowCursorScript(abc::ScriptableABC* node);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;
    };
}

#endif //JAGE_FOLLOW_CURSOR_SCRIPT_HPP
