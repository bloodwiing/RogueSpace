#ifndef JAGE_EVENT_ABC_HPP
#define JAGE_EVENT_ABC_HPP

#include <vector>

namespace jage::event::abc {

    template<class Type, class... Args>
    class EventABC {
    public:
        typedef Type EventType;

        class Manager;
        class Handler;

        ~EventABC();

        virtual void notify(Args...) = 0;

    protected:
        void setHandler(Handler* handler);

    private:
        Handler* m_handler = nullptr;
    };

    template<class Type, class... Args>
    class EventABC<Type, Args...>::Handler {
    public:
        friend class EventABC<Type, Args...>;

        explicit Handler(Type* handle);

        [[nodiscard]] Type* getHandle() const;

    private:
        Type* m_handle = nullptr;
    };

    template<class Type, class... Args>
    class EventABC<Type, Args...>::Manager {
    public:
        void notifyAll(Args&&... args);

        void addHandler(Type& event);
        Manager& operator+=(Type& event);

    protected:
        std::vector<EventABC<Type, Args...>::Handler*> m_handlers;
    };
}

#include "eventabc_impl.tpp"

#endif //JAGE_EVENT_ABC_HPP
