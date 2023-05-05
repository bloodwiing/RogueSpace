#ifndef COMPONENT_CLASS_H
#define COMPONENT_CLASS_H

namespace jage::script::abc {

    /// \brief      Work In Progress
    class ScriptABC {
    public:
        virtual void onSpawn() {};
        virtual void onUpdate() {};
        virtual void onDeath() {};
    };
}

#endif //COMPONENT_CLASS_H
