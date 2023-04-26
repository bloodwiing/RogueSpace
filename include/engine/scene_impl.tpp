template<class T>
T *Engine::Scene::addChild(std::string name) {
    return ActorBase::addChild<T>(this, nullptr, name);
}

template<class T, class... Args>
T *Engine::Scene::addChild(std::string name, Args&&... args) {
    return ActorBase::addChild<T>(this, nullptr, name, std::forward<Args>(args)...);
}

template<class T>
T *Engine::Scene::addVolatileChild(std::string name) {
    static_assert(std::is_base_of<ActorBase, T>::value, "Cannot add a non-Hierarchy child");
    auto child = std::make_shared<T>(this, nullptr, name);
    m_volatileActors.add(child);
    return child.get();
}

template<class T, class... Args>
T *Engine::Scene::addVolatileChild(std::string name, Args&&... args) {
    static_assert(std::is_base_of<ActorBase, T>::value, "Cannot add a non-Hierarchy child");
    auto child = std::make_shared<T>(this, nullptr, name, std::forward<Args>(args)...);
    m_volatileActors.add(child);
    return child.get();
}
