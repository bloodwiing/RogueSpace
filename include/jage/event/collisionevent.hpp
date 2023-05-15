#ifndef JAGE_COLLISION_EVENT_HPP
#define JAGE_COLLISION_EVENT_HPP

#include "jage/actor/staticactor.hpp"
#include "jage/event/abc/event_abc.hpp"

namespace jage::event {

    class CollisionEvent : public abc::EventABC<CollisionEvent, jage::actor::StaticActor*> {
    public:
        void notify(jage::actor::StaticActor *) override;
    };
}

#endif //JAGE_COLLISION_EVENT_HPP
