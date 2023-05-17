#ifndef ROGUESPACE_NODE_ABC_HPP
#define ROGUESPACE_NODE_ABC_HPP

#include <string>
#include <memory>
#include <map>

namespace jage::node::abc {

    template<class TNode>
    class NodeABC : public std::enable_shared_from_this<NodeABC<TNode>> {
    public:
        struct ChildEntry {
            std::shared_ptr<TNode> value;
            uint16_t nameRepeat;
        };

        template<class T>
        T* addChild(TNode* parent, std::string& name);
        template<class T, class... Args>
        T* addChild(TNode* parent, std::string& name, Args&&... args);

    protected:
        [[nodiscard]] virtual std::string getTypeName() const;

        std::string m_name;
        std::map<std::string, ChildEntry> m_children;
        TNode* m_parent;

    private:
        template<class T>
        void internalRegisterChild(std::shared_ptr<T> child);

        NodeABC(const NodeABC&);
        NodeABC& operator=(const NodeABC&);
    };
}

#include "node_abc_impl.tpp"

#endif //ROGUESPACE_NODE_ABC_HPP
