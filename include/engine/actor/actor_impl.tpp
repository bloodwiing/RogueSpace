template<class T>
T* Actor::addChild(std::string name) {
    return ActorBase::addChild<T>(m_scene, this, name);
}

template<class T, class... Args>
T* Actor::addChild(std::string name, Args&&... args) {
    return ActorBase::addChild<T>(m_scene, this, name, std::forward<Args>(args)...);
}
