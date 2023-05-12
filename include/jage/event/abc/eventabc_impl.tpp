template<class Type, class... Args>
jage::event::abc::EventABC<Type, Args...>::~EventABC() {
    if (m_handler != nullptr)
        m_handler->m_handle = nullptr;
}

template<class Type, class... Args>
void jage::event::abc::EventABC<Type, Args...>::setHandler(jage::event::abc::EventABC<Type, Args...>::Handler* handler) {
    if (m_handler != nullptr)
        m_handler->m_handle = nullptr;
    m_handler = handler;
}

template<class Type, class... Args>
jage::event::abc::EventABC<Type, Args...>::Handler::Handler(Type *handle)
    : m_handle(handle)
{

}

template<class Type, class... Args>
Type* jage::event::abc::EventABC<Type, Args...>::Handler::getHandle() const {
    return m_handle;
}

template<class Type, class... Args>
void jage::event::abc::EventABC<Type, Args...>::Manager::notifyAll(Args&&... args) {
    for (auto iter = m_handlers.begin(); iter != m_handlers.end();) {
        auto handle = (*iter)->getHandle();
        if (handle == nullptr) {
            delete handle;
            iter = m_handlers.erase(iter);
            continue;
        }
        handle->notify(args...);
        ++iter;
    }
}

template<class Type, class... Args>
void jage::event::abc::EventABC<Type, Args...>::Manager::addHandler(Type& event) {
    auto* handler = new Handler(&event);
    event.setHandler(handler);
    m_handlers.push_back(handler);
}

template<class Type, class... Args>
typename jage::event::abc::EventABC<Type, Args...>::Manager& jage::event::abc::EventABC<Type, Args...>::Manager::operator+=(Type& event) {
    addHandler(event);
    return *this;
}
