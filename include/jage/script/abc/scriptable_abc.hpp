#ifndef JAGE_SCRIPTABLE_ABC_HPP
#define JAGE_SCRIPTABLE_ABC_HPP

#include <vector>
#include <memory>
#include "jage/script/abc/script_abc.hpp"

namespace jage::script::abc {

    class ScriptableABC {
    public:
        virtual void update();

        [[nodiscard]] virtual bool isDead() const = 0;

        template<class T>
        T* attachScript();
        template<class T, class... Args>
        T* attachScript(Args&&... args);

        template<class T>
        T* findScript();

    private:
        /// A list of attachable Scripts
        std::vector<std::shared_ptr<jage::script::abc::ScriptABC>> m_scripts;
    };
}

#include "scriptable_abc_impl.tpp"

#endif //JAGE_SCRIPTABLE_ABC_HPP
