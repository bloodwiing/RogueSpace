#ifndef JAGE_TIMER_EVENT_HPP
#define JAGE_TIMER_EVENT_HPP

#include <functional>
#include "jage/event/abc/eventabc.hpp"

namespace jage::event {

    class TimerEvent : public abc::EventABC<> {
    public:
        void notify() override;
    };
}

#endif //JAGE_TIMER_EVENT_HPP
