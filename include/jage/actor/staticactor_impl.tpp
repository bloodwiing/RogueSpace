template<class T>
T* jage::actor::StaticActor::addChild(std::string name) {
    return abc::ActorABC::addChild<T>(m_scene, this, name);
}

template<class T, class... Args>
T* jage::actor::StaticActor::addChild(std::string name, Args&&... args) {
    return abc::ActorABC::addChild<T>(m_scene, this, name, std::forward<Args>(args)...);
}
