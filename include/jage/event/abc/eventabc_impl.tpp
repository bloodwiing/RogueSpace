template<class... Args>
void jage::event::abc::EventABC<Args...>::Manager::notifyAll(Args&&... args) {
    for (auto& handler : m_handlers) {
        handler.notify(args...);
    }
}

template<class... Args>
void jage::event::abc::EventABC<Args...>::Manager::addHandler(EventABC<Args...> handler) {
    m_handlers.push_back(handler);
}

template<class... Args>
typename jage::event::abc::EventABC<Args...>::Manager& jage::event::abc::EventABC<Args...>::Manager::operator+=(EventABC<Args...> handler) {
    m_handlers.push_back(handler);
    return *this;
}
