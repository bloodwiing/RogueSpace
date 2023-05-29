#ifndef JAGE_DAMAGE_EVENT_HPP
#define JAGE_DAMAGE_EVENT_HPP

#include "jage/event/abc/event_abc.hpp"

namespace jage::event {

    class DamageEvent
            : public abc::EventABC<DamageEvent, const float&, const float&, const float&>
    {

    };
}

#endif //JAGE_DAMAGE_EVENT_HPP
