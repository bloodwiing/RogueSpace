#ifndef JAGE_HEAL_EVENT_HPP
#define JAGE_HEAL_EVENT_HPP

#include "jage/event/abc/event_abc.hpp"

namespace jage::event {

    class HealEvent
            : public abc::EventABC<HealEvent, const float&, const float&, const float&>
    {

    };
}

#endif //JAGE_HEAL_EVENT_HPP
