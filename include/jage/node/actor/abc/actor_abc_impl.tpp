template<class T>
T* jage::node::actor::abc::ActorABC::addChild(std::string name, Tag tag) {
    return jage::node::abc::NodeABC<ActorABC>::addChild<T>(this, std::move(name), m_scene, tag, m_volatile);
}

template<class T, class... Args>
T* jage::node::actor::abc::ActorABC::addChild(std::string name, Tag tag, Args&&... args) {
    return jage::node::abc::NodeABC<ActorABC>::addChild<T>(this, std::move(name), m_scene, tag, m_volatile, std::forward<Args>(args)...);
}
