template<class T>
T* Actor::addChild() {
    return ActorBase::addChild<T>(m_scene, this);
}

template<class T, class... Args>
T* Actor::addChild(Args&&... args) {
    return ActorBase::addChild<T>(m_scene, this, std::forward<Args>(args)...);
}
