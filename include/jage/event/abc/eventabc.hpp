#ifndef JAGE_EVENT_ABC_HPP
#define JAGE_EVENT_ABC_HPP

#include <vector>

namespace jage::event::abc {

    template<class Type, class... Args>
    class EventABC {
    public:
        typedef Type EventType;

        class Manager;

        virtual void notify(Args...) = 0;
    };

    template<class Type, class... Args>
    class EventABC<Type, Args...>::Manager {
    public:
        void notifyAll(Args&&... args);

        void addHandler(Type handler);
        Manager& operator+=(Type handler);

    protected:
        std::vector<Type> m_handlers;
    };
}

#include "eventabc_impl.tpp"

#endif //JAGE_EVENT_ABC_HPP
