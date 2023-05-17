template<class TNode>
template<class T>
void jage::node::abc::NodeABC<TNode>::internalRegisterChild(std::shared_ptr<T> child) {
    static_assert(std::is_base_of<TNode, T>::value, "Cannot register a non-Hierarchy child");

    // Prepare as if key is unique
    NodeABC<TNode>::ChildEntry entry {
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

template<class TNode>
template<class T>
T* jage::node::abc::NodeABC<TNode>::addChild(TNode* parent, std::string& name) {
    static_assert(std::is_base_of<TNode, T>::value, "Cannot add a non-Hierarchy child");
    auto child = std::make_shared<T>(parent, name);
    internalRegisterChild(child);
    return child.get();
}

template<class TNode>
template<class T, class... Args>
T* jage::node::abc::NodeABC<TNode>::addChild(TNode* parent, std::string& name, Args&&... args) {
    static_assert(std::is_base_of<TNode, T>::value, "Cannot add a non-Hierarchy child");
    auto child = std::make_shared<T>(parent, name, std::forward<Args>(args)...);
    internalRegisterChild(child);
    return child.get();
}

template<class TNode>
std::string jage::node::abc::NodeABC<TNode>::getTypeName() const {
    return "Node ABC";
}
