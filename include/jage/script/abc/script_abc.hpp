#ifndef JAGE_SCRIPT_ABC_HPP
#define JAGE_SCRIPT_ABC_HPP

#include <stdexcept>

namespace jage::actor::abc {
    class ActorABC;
}

namespace jage::script::abc {

    class ScriptABC {
    public:
        class AttachError;

        virtual void onAttach() = 0;
        virtual void onSpawn() = 0;
        virtual void onUpdate() = 0;
        virtual void onDeath() = 0;

        virtual void onKeyboardInput() {};
        virtual void onMouseInput() {};
    };

    class ScriptABC::AttachError : std::invalid_argument {
    public:
        AttachError();
    };
}

#endif //JAGE_SCRIPT_ABC_HPP
