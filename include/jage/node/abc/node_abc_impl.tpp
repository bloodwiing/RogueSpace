template<class TNode>
jage::node::abc::NodeABC<TNode>::NodeABC(JAGE_NODE_ARGS(TNode))
    : m_parent(parent)
    , m_name(std::move(name))
{

}

template<class TNode>
template<class T>
void jage::node::abc::NodeABC<TNode>::internalRegisterChild(std::shared_ptr<T> child) {
    static_assert(std::is_base_of<NodeType, T>::value, "Cannot register a non-Hierarchy child");

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
T* jage::node::abc::NodeABC<TNode>::addChild(JAGE_NODE_ARGS(TNode)) {
    static_assert(std::is_base_of<NodeType, T>::value, "Cannot add a non-Hierarchy child");
    auto child = std::make_shared<T>(parent, name);
    internalRegisterChild(child);
    child->spawn();
    return child.get();
}

template<class TNode>
template<class T, class... Args>
T* jage::node::abc::NodeABC<TNode>::addChild(JAGE_NODE_ARGS(TNode), Args&&... args) {
    static_assert(std::is_base_of<NodeType, T>::value, "Cannot add a non-Hierarchy child");
    auto child = std::make_shared<T>(parent, name, std::forward<Args>(args)...);
    internalRegisterChild(child);
    child->spawn();
    return child.get();
}

template<class TNode>
std::map<std::string, typename jage::node::abc::NodeABC<TNode>::ChildEntry> jage::node::abc::NodeABC<TNode>::getChildren() const {
    return m_children;
}

template<class TNode>
TNode* jage::node::abc::NodeABC<TNode>::getChild(const std::string &name) const {
    if (m_children.find(name) == m_children.end())
        return nullptr;
    return m_children.at(name).value.get();
}

template<class TNode>
TNode* jage::node::abc::NodeABC<TNode>::getParent() const {
    return m_parent;
}

template<class TNode>
std::string jage::node::abc::NodeABC<TNode>::getName() const {
    return m_name;
}

template<class TNode>
std::string jage::node::abc::NodeABC<TNode>::toHierarchyString(uint16_t indent /* = 0 */) const {
    std::string result = m_name + ": " + getTypeName() + "\n";
    for (const auto& iter : m_children) {
        result += std::string(" | ", indent * 3) + " > ";
        result += iter.second.value->toHierarchyString(indent + 1);
    }
    return result;
}

template<class TNode>
void jage::node::abc::NodeABC<TNode>::update() {
    for (auto iter = m_children.begin(); iter != m_children.end();) {
        std::shared_ptr<NodeType> child = iter->second.value;
        if (child) {
            try {
                child->update();
            } catch (std::exception& e) {
                std::cerr << e.what();
                iter = m_children.erase(iter);
                continue;
            }
            if (child->isDead()) {
                iter = m_children.erase(iter);
            } else {
                ++iter;
            }
        } else {
            iter = m_children.erase(iter);
        }
    }
}

template<class TNode>
void jage::node::abc::NodeABC<TNode>::draw() {
    for (auto& [name, child] : m_children) {
        if (child.value)
            child.value->draw();
    }
}

template<class TNode>
std::string jage::node::abc::NodeABC<TNode>::getTypeName() const {
    return "Node ABC";
}

template<class TNode>
std::ostream& operator<<(std::ostream& stream, jage::node::abc::NodeABC<TNode> *node) {
    stream << node->toHierarchyString();
    return stream;
}
