template<class T>
T *jage::actor::Scene::addChild(JAGE_SCENE_ACTOR_ARGS) {
    return jage::node::abc::NodeABC<NodeType>::addChild<T>(nullptr, std::move(name), this, tag, false);
}

template<class T, class... Args>
T *jage::actor::Scene::addChild(JAGE_SCENE_ACTOR_ARGS, Args&&... args) {
    return jage::node::abc::NodeABC<NodeType>::addChild<T>(nullptr, std::move(name), this, tag, false, std::forward<Args>(args)...);
}

template<class T>
T *jage::actor::Scene::addVolatileChild(JAGE_SCENE_ACTOR_ARGS) {
    static_assert(std::is_base_of<NodeType, T>::value, "Cannot add a non-Hierarchy child");
    auto child = std::make_shared<T>(nullptr, std::move(name), this, tag, true);
    m_volatileActors.add(child);
    return child.get();
}

template<class T, class... Args>
T *jage::actor::Scene::addVolatileChild(JAGE_SCENE_ACTOR_ARGS, Args&&... args) {
    static_assert(std::is_base_of<NodeType, T>::value, "Cannot add a non-Hierarchy child");
    auto child = std::make_shared<T>(nullptr, std::move(name), this, tag, true, std::forward<Args>(args)...);
    m_volatileActors.add(child);
    return child.get();
}
