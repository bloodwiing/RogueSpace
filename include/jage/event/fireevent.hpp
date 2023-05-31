#ifndef JAGE_FIRE_EVENT_HPP
#define JAGE_FIRE_EVENT_HPP

#include "jage/event/abc/event_abc.hpp"

namespace jage::event {

    class FireEvent
            : public abc::EventABC<FireEvent>
    {

    };
}

#endif //JAGE_FIRE_EVENT_HPP
