#include "engine/hierarchycontainer.h"

template<class THead, class TElem>
HierarchyContainer<THead, TElem>::HierarchyContainer(HierarchyContainer *parent)
    : m_parent(parent)
{ }

template<class THead, class TElem>
HierarchyContainer<THead, TElem>::~HierarchyContainer() {
    for (const TElem* child : m_children) {
        delete child;
    }
}

template<class THead, class TElem>
std::vector<HierarchyContainer<THead, TElem>* > HierarchyContainer<THead, TElem>::getChildren() const {
    return m_children;
}

template<class THead, class TElem>
template<class T>
T* HierarchyContainer<THead, TElem>::addChild(const THead* head) {
    static_assert(std::is_base_of<T, HierarchyContainer<THead, TElem> >::value, "Cannot add a non-Hierarchy child");
    T* child = new T(head, this);
    m_children.push_back(child);
}

template<class THead, class TElem>
HierarchyContainer<THead, TElem>* HierarchyContainer<THead, TElem>::getParent() const {
    return m_parent;
}
