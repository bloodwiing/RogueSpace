template<class T>
T *jage::actor::Scene::addChild(std::string name) {
    return abc::ActorABC::addChild<T>(this, nullptr, name);
}

template<class T, class... Args>
T *jage::actor::Scene::addChild(std::string name, Args&&... args) {
    return abc::ActorABC::addChild<T>(this, nullptr, name, std::forward<Args>(args)...);
}

template<class T>
T *jage::actor::Scene::addVolatileChild(std::string name) {
    static_assert(std::is_base_of<abc::ActorABC, T>::value, "Cannot add a non-Hierarchy child");
    auto child = std::make_shared<T>(this, nullptr, name);
    m_volatileActors.add(child);
    return child.get();
}

template<class T, class... Args>
T *jage::actor::Scene::addVolatileChild(std::string name, Args&&... args) {
    static_assert(std::is_base_of<abc::ActorABC, T>::value, "Cannot add a non-Hierarchy child");
    auto child = std::make_shared<T>(this, nullptr, name, std::forward<Args>(args)...);
    m_volatileActors.add(child);
    return child.get();
}
