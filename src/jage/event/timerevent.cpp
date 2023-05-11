#include "jage/event/timerevent.hpp"

#include <iostream>
#include <utility>

//void jage::event::CollisionEvent::notify(jage::actor::DynamicActor) {
//
//}
//
//void jage::event::DamageEvent::notify(jage::actor::DynamicActor, float) {
//
//}

void jage::event::DummyEvent::notify(int number) {
    std::cout << m_text << " and " << number << std::endl;
}

jage::event::DummyEvent::DummyEvent(std::string text)
    : m_text(std::move(text))
{

}
