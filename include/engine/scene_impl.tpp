template<class T>
T *Scene::addChild() {
    return ActorBase::addChild<T>(this, nullptr);
}
