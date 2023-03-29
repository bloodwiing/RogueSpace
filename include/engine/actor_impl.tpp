template<class T>
T *Actor::addChild() {
    return ActorBase::addChild<T>(m_scene, this);
}
