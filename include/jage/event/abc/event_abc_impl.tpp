template<class Type, class... Args>
void jage::event::abc::EventABC<Type, Args...>::Manager::notifyAll(Args&&... args) {
    for (auto iter = m_listeners.begin(); iter != m_listeners.end();) {
        if (iter->expired()) {
            iter = m_listeners.erase(iter);
            continue;
        }
        iter->lock()->notify(args...);
        ++iter;
    }
}

template<class Type, class... Args>
void jage::event::abc::EventABC<Type, Args...>::Manager::addListener(std::shared_ptr<Type>& event) {
    m_listeners.push_back(event);
}

template<class Type, class... Args>
typename Type::Manager& jage::event::abc::EventABC<Type, Args...>::Manager::operator+=(std::shared_ptr<Type>& event) {
    addListener(event);
    return *this;
}
