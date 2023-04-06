template<class T>
T *Scene::addChild(std::string name) {
    return ActorBase::addChild<T>(this, nullptr, name);
}

template<class T, class... Args>
T *Scene::addChild(std::string name, Args&&... args) {
    return ActorBase::addChild<T>(this, nullptr, name, std::forward<Args>(args)...);
}
