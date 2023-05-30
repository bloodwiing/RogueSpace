#ifndef JAGE_SCORE_UPDATE_EVENT_HPP
#define JAGE_SCORE_UPDATE_EVENT_HPP

#include "jage/event/abc/event_abc.hpp"

namespace jage::event {

    class ScoreUpdateEvent
            : public abc::EventABC<ScoreUpdateEvent, long>
    {

    };
}

#endif //JAGE_SCORE_UPDATE_EVENT_HPP
