#ifndef JAGE_EVENT_ABC_HPP
#define JAGE_EVENT_ABC_HPP

#include <vector>
#include <memory>

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
        Manager() = default;

        void notifyAll(Args&... args);

        void addListener(const std::weak_ptr<Type>& event);
        typename Type::Manager& operator+=(const std::weak_ptr<Type>& event);

    protected:
        std::vector<std::weak_ptr<Type>> m_listeners;

        Manager(Manager& ref) = default;
        Manager& operator=(const Manager& ref) = default;
    };
}

#include "event_abc_impl.tpp"

#endif //JAGE_EVENT_ABC_HPP
