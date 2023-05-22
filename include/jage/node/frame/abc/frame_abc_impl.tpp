template<class T>
T* jage::node::frame::abc::FrameABC::addChild(std::string name) {
    return jage::node::abc::NodeABC<FrameABC>::addChild<T>(this, std::move(name), m_canvas, this);
}

template<class T, class... Args>
T* jage::node::frame::abc::FrameABC::addChild(std::string name, Args&&... args) {
    return jage::node::abc::NodeABC<FrameABC>::addChild<T>(this, std::move(name), m_canvas, this, std::forward<Args>(args)...);
}