template<class T>
T* jage::actor::Actor::addChild(std::string name) {
    return abc::ActorABC::addChild<T>(m_scene, this, name);
}

template<class T, class... Args>
T* jage::actor::Actor::addChild(std::string name, Args&&... args) {
    return abc::ActorABC::addChild<T>(m_scene, this, name, std::forward<Args>(args)...);
}
