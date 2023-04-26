#ifndef COMPONENT_CLASS_H
#define COMPONENT_CLASS_H

namespace Engine {

    /// \brief      Work In Progress
    class Script {
    public:
        virtual void onSpawn() {};
        virtual void onUpdate() {};
        virtual void onDeath() {};
    };
}

#endif //COMPONENT_CLASS_H
