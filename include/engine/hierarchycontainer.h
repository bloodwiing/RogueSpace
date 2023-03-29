#ifndef HIERARCHY_CONTAINER_CLASS_H
#define HIERARCHY_CONTAINER_CLASS_H

#include <vector>

template<class THead, class TElem>
class HierarchyContainer {
public:
    explicit HierarchyContainer(HierarchyContainer* parent);
    ~HierarchyContainer();

    [[nodiscard]] std::vector<HierarchyContainer*> getChildren() const;
    template<class T>
    T* addChild(const THead* head);

    [[nodiscard]] HierarchyContainer* getParent() const;

protected:
    std::vector<HierarchyContainer*> m_children;
    HierarchyContainer* m_parent;
};

#endif //HIERARCHY_CONTAINER_CLASS_H
