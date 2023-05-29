#ifndef JAGE_COLLISION_EVENT_HPP
#define JAGE_COLLISION_EVENT_HPP

#include "jage/node/actor/staticactor.hpp"
#include "jage/event/abc/event_abc.hpp"

namespace jage::event {

    class CollisionEvent
            : public abc::EventABC<CollisionEvent, jage::node::actor::StaticActor*>
    {

    };
}

#endif //JAGE_COLLISION_EVENT_HPP
