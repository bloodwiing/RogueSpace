#ifndef JAGE_CURSOR_DISTANCE_OPACITY_SCRIPT
#define JAGE_CURSOR_DISTANCE_OPACITY_SCRIPT

#include "jage/script/abc/script_abc.hpp"
#include "jage/node/frame/spriteframe.hpp"

namespace jage::script::frame {

    class CursorDistanceOpacityScript
            : public abc::AttachableScriptABC<jage::node::frame::SpriteFrame>
    {
    public:
        CursorDistanceOpacityScript(abc::ScriptableABC* node, float minDistance, float maxDistance, float maxOpacity);

        void onAttach() override;
        void onSpawn() override;
        void onUpdate() override;
        void onDeath() override;

    private:
        float m_minDistance;
        float m_maxDistance;
        float m_maxOpacity;
    };
}

#endif //JAGE_CURSOR_DISTANCE_OPACITY_SCRIPT
