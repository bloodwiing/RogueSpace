#ifndef JAGE_NODE_ABC_HPP
#define JAGE_NODE_ABC_HPP

#include <string>
#include <memory>
#include <map>
#include <iostream>

#include "jage/graphics/shader.hpp"

#define JAGE_NODE_ARGS(Type) Type* parent, std::string name

namespace jage::node::abc {

    template<class TNode>
    class NodeABC : public std::enable_shared_from_this<TNode> {
    public:
        struct ChildEntry {
            std::shared_ptr<TNode> value;
            uint16_t nameRepeat;
        };

        typedef TNode NodeType;

        NodeABC(JAGE_NODE_ARGS(TNode));
        NodeABC(const NodeABC&) = delete;
        NodeABC& operator=(const NodeABC&) = delete;

        template<class T>
        T* addChild(JAGE_NODE_ARGS(TNode));
        template<class T, class... Args>
        T* addChild(JAGE_NODE_ARGS(TNode), Args&&... args);

        [[nodiscard]] std::string toHierarchyString(uint16_t indent = 0) const;

        virtual void update();
        virtual void draw(jage::graphics::Shader& shader);

    protected:
        [[nodiscard]] virtual std::string getTypeName() const;

        std::string m_name;
        std::map<std::string, ChildEntry> m_children;
        TNode* m_parent;

    private:
        template<class T>
        void internalRegisterChild(std::shared_ptr<T> child);
    };
}

template<class TNode>
std::ostream& operator<<(std::ostream& stream, jage::node::abc::NodeABC<TNode>* node);

#include "node_abc_impl.tpp"

#endif //JAGE_NODE_ABC_HPP
