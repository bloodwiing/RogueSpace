template<class T>
T* ActorBase::addChild(Scene* scene, ActorBase* parent) {
    static_assert(std::is_base_of<ActorBase, T>::value, "Cannot add a non-Hierarchy child");
    T* child = new T(scene, parent);
    m_children.push_back(child);
    return child;
}
