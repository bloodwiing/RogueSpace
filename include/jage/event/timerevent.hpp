#ifndef JAGE_TIMER_EVENT_HPP
#define JAGE_TIMER_EVENT_HPP

#include <functional>
#include "jage/event/abc/eventabc.hpp"
#include "jage/actor/dynamicactor.hpp"

namespace jage::event {

    class DummyEvent : public abc::EventABC<DummyEvent, int> {
    public:
        explicit DummyEvent(std::string text);
        const std::string m_text;

        void notify(int number) override;
    };

    class CollisionEvent : public abc::EventABC<CollisionEvent, jage::actor::DynamicActor> {
    public:
        void notify(jage::actor::DynamicActor) override;
    };

    class DamageEvent : public abc::EventABC<DamageEvent, jage::actor::DynamicActor, float> {
    public:
        void notify(jage::actor::DynamicActor, float) override;
    };
}

#endif //JAGE_TIMER_EVENT_HPP
