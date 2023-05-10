#ifndef JAGE_SCRIPT_ABC_HPP
#define JAGE_SCRIPT_ABC_HPP

#include <stdexcept>

namespace jage::actor::abc {
    class ActorABC;
}

namespace jage::script::abc {

    class ScriptABC {
    public:
        virtual void onAttach() = 0;
        virtual void onSpawn() = 0;
        virtual void onUpdate() = 0;
        virtual void onDeath() = 0;

        virtual void onKeyboardInput() {};
        virtual void onMouseInput() {};
    };

    template<class TNode>
    class AttachableScriptABC : public ScriptABC {
    public:
        typedef TNode* RequiredNodeType;

        class AttachError;

    protected:
        TNode* m_node;

        void validate(jage::actor::abc::ActorABC* node);
    };

    template<class TNode>
    class AttachableScriptABC<TNode>::AttachError : std::invalid_argument {
    public:
        AttachError();
    };
}

#include "script_abc_impl.tpp"

#endif //JAGE_SCRIPT_ABC_HPP
