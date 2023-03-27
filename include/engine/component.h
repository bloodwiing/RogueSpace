#ifndef COMPONENT_CLASS_H
#define COMPONENT_CLASS_H

class Component {
public:
    virtual void onSpawn() {};
    virtual void onUpdate() {};
    virtual void onDeath() {};
};

#endif //COMPONENT_CLASS_H
