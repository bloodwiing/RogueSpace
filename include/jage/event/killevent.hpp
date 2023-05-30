#ifndef JAGE_KILL_EVENT_HPP
#define JAGE_KILL_EVENT_HPP

#include "jage/event/abc/event_abc.hpp"
#include "jage/node/actor/dynamicactor.hpp"

namespace jage::event {

    class KillEvent
            : public abc::EventABC<KillEvent, jage::node::actor::DynamicActor*>
    {

    };
}

#endif //JAGE_KILL_EVENT_HPP
