#ifndef JAGE_DAMAGE_EVENT_HPP
#define JAGE_DAMAGE_EVENT_HPP

#include "jage/event/abc/event_abc.hpp"
#include "jage/node/actor/dynamicactor.hpp"

namespace jage::event {

    class DamageEvent
            : public abc::EventABC<DamageEvent, node::actor::DynamicActor*, const float&, const float&, const float&>
    {

    };
}

#endif //JAGE_DAMAGE_EVENT_HPP
