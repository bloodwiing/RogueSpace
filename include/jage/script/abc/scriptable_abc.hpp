#ifndef JAGE_SCRIPTABLE_ABC_HPP
#define JAGE_SCRIPTABLE_ABC_HPP

#include <vector>
#include <memory>

#include "jage/node/abc/dying_abc.hpp"
#include "jage/script/abc/script_abc.hpp"

namespace jage::script::abc {

    class ScriptableABC : public node::abc::DyingABC {
    public:
        virtual void update();

        template<class T>
        std::weak_ptr<T> attachScript();
        template<class T, class... Args>
        std::weak_ptr<T> attachScript(Args&&... args);

        template<class T>
        std::weak_ptr<T> findScript();

    private:
        /// A list of attachable Scripts
        std::vector<std::shared_ptr<jage::script::abc::ScriptABC>> m_scripts;
    };
}

#include "scriptable_abc_impl.tpp"

#endif //JAGE_SCRIPTABLE_ABC_HPP
