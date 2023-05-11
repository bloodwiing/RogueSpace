template<class Type, class... Args>
void jage::event::abc::EventABC<Type, Args...>::Manager::notifyAll(Args&&... args) {
    for (auto& handler : m_handlers) {
        handler.notify(args...);
    }
}

template<class Type, class... Args>
void jage::event::abc::EventABC<Type, Args...>::Manager::addHandler(Type handler) {
    m_handlers.push_back(handler);
}

template<class Type, class... Args>
typename jage::event::abc::EventABC<Type, Args...>::Manager& jage::event::abc::EventABC<Type, Args...>::Manager::operator+=(Type handler) {
    m_handlers.push_back(handler);
    return *this;
}
