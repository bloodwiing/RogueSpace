template<class T>
T *Scene::addChild() {
    return ActorBase::addChild<T>(this, nullptr);
}

template<class T, class... Args>
T *Scene::addChild(Args&&... args) {
    return ActorBase::addChild<T>(this, nullptr, std::forward<Args>(args)...);
}
