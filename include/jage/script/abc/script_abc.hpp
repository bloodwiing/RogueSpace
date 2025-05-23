#ifndef JAGE_SCRIPT_ABC_HPP
#define JAGE_SCRIPT_ABC_HPP

#include <stdexcept>
#include <memory>

namespace jage::node::actor::abc {
    class ActorABC;
}

namespace jage::script::abc {

    class ScriptableABC;

    class ScriptABC {
    public:
        ScriptABC() = default;
        ~ScriptABC() = default;
        ScriptABC& operator=(const ScriptABC& ref) = default;

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
        class RequireError;

    protected:
        TNode* m_node;

        void validate(ScriptableABC* node);
        template<class T>
        std::weak_ptr<T> dependsOn();
    };

    template<class TNode>
    class AttachableScriptABC<TNode>::AttachError : std::invalid_argument {
    public:
        AttachError();
    };

    template<class TNode>
    class AttachableScriptABC<TNode>::RequireError : std::runtime_error {
    public:
        RequireError();
    };
}

#include "script_abc_impl.tpp"

#endif //JAGE_SCRIPT_ABC_HPP
