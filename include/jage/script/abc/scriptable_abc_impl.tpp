template<class T>
T* jage::script::abc::ScriptableABC::attachScript() {
    static_assert(std::is_base_of<jage::script::abc::ScriptABC, T>::value, "Attached class needs to be a ScriptABC type");
    auto child = std::make_shared<T>(this);
    m_scripts.push_back(child);
    child->onAttach();
    return child.get();
}

template<class T, class... Args>
T* jage::script::abc::ScriptableABC::attachScript(Args&&... args) {
    static_assert(std::is_base_of<jage::script::abc::ScriptABC, T>::value, "Attached class needs to be a ScriptABC type");
    auto child = std::make_shared<T>(this, std::forward<Args>(args)...);
    m_scripts.push_back(child);
    child->onAttach();
    return child.get();
}

template<class T>
T* jage::script::abc::ScriptableABC::findScript() {
    for (auto& script : m_scripts) {
        auto* cast = dynamic_cast<T*>(script.get());
        if (cast != nullptr)
            return cast;
    }
    return nullptr;
}
