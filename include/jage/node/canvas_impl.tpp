template<class T>
T *jage::node::Canvas::addChild(JAGE_CANVAS_FRAME_ARGS) {
    return jage::node::abc::NodeABC<NodeType>::addChild<T>(nullptr, std::move(name), this, this);
}

template<class T, class... Args>
T *jage::node::Canvas::addChild(JAGE_CANVAS_FRAME_ARGS, Args&&... args) {
    return jage::node::abc::NodeABC<NodeType>::addChild<T>(nullptr, std::move(name), this, this, std::forward<Args>(args)...);
}