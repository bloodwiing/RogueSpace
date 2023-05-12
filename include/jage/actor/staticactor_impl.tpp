template<class T>
T* jage::actor::StaticActor::addChild(std::string name, Tag tag) {
    return abc::ActorABC::addChild<T>(m_scene, this, name, tag, m_volatile);
}

template<class T, class... Args>
T* jage::actor::StaticActor::addChild(std::string name, Tag tag, Args&&... args) {
    return abc::ActorABC::addChild<T>(m_scene, this, name, tag, m_volatile, std::forward<Args>(args)...);
}

template<class T>
T* jage::actor::StaticActor::attachScript() {
    static_assert(std::is_base_of<jage::script::abc::ScriptABC, T>::value, "Attached class needs to be a ScriptABC type");
    auto child = std::make_shared<T>(this);
    m_scripts.push_back(child);
    child->onAttach();
    return child.get();
}

template<class T, class... Args>
T* jage::actor::StaticActor::attachScript(Args&&... args) {
    static_assert(std::is_base_of<jage::script::abc::ScriptABC, T>::value, "Attached class needs to be a ScriptABC type");
    auto child = std::make_shared<T>(this, std::forward<Args>(args)...);
    m_scripts.push_back(child);
    child->onAttach();
    return child.get();
}

template<class T>
T* jage::actor::StaticActor::findScript() {
    for (auto& script : m_scripts) {
        auto* cast = dynamic_cast<T*>(script.get());
        if (cast != nullptr)
            return cast;
    }
    return nullptr;
}
