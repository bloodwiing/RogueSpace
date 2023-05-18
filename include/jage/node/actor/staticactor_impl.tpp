template<class T>
T* jage::node::actor::StaticActor::addChild(std::string name, Tag tag) {
    return abc::ActorABC::addChild<T>(this, name, m_scene, tag, m_volatile);
}

template<class T, class... Args>
T* jage::node::actor::StaticActor::addChild(std::string name, Tag tag, Args&&... args) {
    return abc::ActorABC::addChild<T>(this, name, m_scene, tag, m_volatile, std::forward<Args>(args)...);
}
