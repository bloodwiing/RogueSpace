template<class TNode>
void jage::script::abc::AttachableScriptABC<TNode>::validate(jage::actor::abc::ActorABC* node) {
    auto* cast = dynamic_cast<TNode*>(node);
    if (cast == nullptr)
        throw abc::AttachableScriptABC<TNode>::AttachError();
    m_node = cast;
}

template<class TNode>
jage::script::abc::AttachableScriptABC<TNode>::AttachError::AttachError()
    : std::invalid_argument("Could not attach to Actor - invalid type")
{

}