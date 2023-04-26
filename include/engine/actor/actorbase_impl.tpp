template<class T>
void ActorBase::internalRegisterChild(std::shared_ptr<T> child) {
    static_assert(std::is_base_of<ActorBase, T>::value, "Cannot register a non-Hierarchy child");

    // Prepare as if key is unique
    ActorBase::ChildEntry entry {
        .value = child,
        .nameRepeat = 1
    };

    // Find if key is actually unique
    if (m_children.find(child->m_name) != m_children.end()) {
        auto& existingEntry = m_children.at(child->m_name);
        // Try to create the child as "{name} ({repeat})", example: "Bullet (2)"
        // Recursive in case a name with parenthesis was added manually before, will stack parenthesis as a result
        child->m_name += " (" + std::to_string(++existingEntry.nameRepeat) + ")";
        internalRegisterChild(child);
        return;
    }

    // If code reached here, we can finally add the child
    m_children[child->m_name] = entry;
}

template<class T>
T* ActorBase::addChild(Scene* scene, ActorBase* parent, std::string& name) {
    static_assert(std::is_base_of<ActorBase, T>::value, "Cannot add a non-Hierarchy child");
    auto child = std::make_shared<T>(scene, parent, name);
    internalRegisterChild(child);
    return child.get();
}

template<class T, class... Args>
T* ActorBase::addChild(Scene* scene, ActorBase* parent, std::string& name, Args&&... args) {
    static_assert(std::is_base_of<ActorBase, T>::value, "Cannot add a non-Hierarchy child");
    auto child = std::make_shared<T>(scene, parent, name, std::forward<Args>(args)...);
    internalRegisterChild(child);
    return child.get();
}
