template<class T>
T *jage::actor::Scene::addChild(std::string name, Tag tag) {
    return abc::ActorABC::addChild<T>(this, nullptr, name, tag);
}

template<class T, class... Args>
T *jage::actor::Scene::addChild(std::string name, Tag tag, Args&&... args) {
    return abc::ActorABC::addChild<T>(this, nullptr, name, tag, std::forward<Args>(args)...);
}

template<class T>
T *jage::actor::Scene::addVolatileChild(std::string name, Tag tag) {
    static_assert(std::is_base_of<abc::ActorABC, T>::value, "Cannot add a non-Hierarchy child");
    auto child = std::make_shared<T>(this, nullptr, name, tag);
    m_volatileActors.add(child);
    return child.get();
}

template<class T, class... Args>
T *jage::actor::Scene::addVolatileChild(std::string name, Tag tag, Args&&... args) {
    static_assert(std::is_base_of<abc::ActorABC, T>::value, "Cannot add a non-Hierarchy child");
    auto child = std::make_shared<T>(this, nullptr, name, tag, std::forward<Args>(args)...);
    m_volatileActors.add(child);
    return child.get();
}
