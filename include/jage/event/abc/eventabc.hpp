#ifndef JAGE_EVENT_ABC_HPP
#define JAGE_EVENT_ABC_HPP

#include <vector>

namespace jage::event::abc {

    template<class... Args>
    class EventABC {
    public:
        class Manager;

        virtual void notify(Args&&...) = 0;
    };

    template<class... Args>
    class EventABC<Args...>::Manager {
    public:
        void notifyAll(Args&&... args);

        void addHandler(EventABC<Args...> handler);
        Manager& operator+=(EventABC<Args...> handler);

    protected:
        std::vector<EventABC<Args...>> m_handlers;
    };
}

#include "eventabc_impl.tpp"

#endif //JAGE_EVENT_ABC_HPP
