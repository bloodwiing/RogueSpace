#ifndef JAGE_SCRIPT_ABC_HPP
#define JAGE_SCRIPT_ABC_HPP

namespace jage::script::abc {

    /// \brief      Work In Progress
    class ScriptABC {
    public:
        virtual void onSpawn() {};
        virtual void onUpdate() {};
        virtual void onDeath() {};
    };
}

#endif //JAGE_SCRIPT_ABC_HPP
