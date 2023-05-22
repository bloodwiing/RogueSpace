#include "scriptable_abc.hpp"

template<class TNode>
void jage::script::abc::AttachableScriptABC<TNode>::validate(jage::script::abc::ScriptableABC* node) {
    auto* cast = dynamic_cast<TNode*>(node);
    if (cast == nullptr)
        throw abc::AttachableScriptABC<TNode>::AttachError();
    m_node = cast;
}

template<class TNode>
template<class T>
T* jage::script::abc::AttachableScriptABC<TNode>::dependsOn() {
   T* result = m_node->template findScript<T>();
   if (result == nullptr)
       throw abc::AttachableScriptABC<TNode>::RequireError();
   return result;
}

template<class TNode>
jage::script::abc::AttachableScriptABC<TNode>::AttachError::AttachError()
    : std::invalid_argument("Could not attach Script to Node - invalid type")
{

}

template<class TNode>
jage::script::abc::AttachableScriptABC<TNode>::RequireError::RequireError()
    : std::runtime_error("Could not attach Script to Node - missing requirement")
{

}