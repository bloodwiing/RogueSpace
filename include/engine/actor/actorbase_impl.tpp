template<class T>
T* ActorBase::addChild(Scene* scene, ActorBase* parent) {
    static_assert(std::is_base_of<ActorBase, T>::value, "Cannot add a non-Hierarchy child");
    T* child = new T(scene, parent);
    m_children.push_back(child);
    return child;
}

template<class T, class... Args>
T* ActorBase::addChild(Scene* scene, ActorBase* parent, Args&&... args) {
    static_assert(std::is_base_of<ActorBase, T>::value, "Cannot add a non-Hierarchy child");
    T* child = new T(scene, parent, std::forward<Args>(args)...);
    m_children.push_back(child);
    return child;
}
