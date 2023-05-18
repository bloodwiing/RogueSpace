template<class T>
T* jage::actor::abc::ActorABC::addChild(JAGE_ACTOR_ARGS) {
    return jage::node::abc::NodeABC<ActorABC>::addChild<T>(parent, name, scene, tag, isVolatile);
}

template<class T, class... Args>
T* jage::actor::abc::ActorABC::addChild(JAGE_ACTOR_ARGS, Args&&... args) {
    return jage::node::abc::NodeABC<ActorABC>::addChild<T>(parent, name, scene, tag, isVolatile, std::forward<Args>(args)...);
}
