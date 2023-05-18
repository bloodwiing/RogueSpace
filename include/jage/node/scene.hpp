#ifndef JAGE_SCENE_HPP
#define JAGE_SCENE_HPP

#include <vector>

#include "jage/node/actor/staticactor.hpp"
#include "jage/node/actor/abc/actor_abc.hpp"
#include "jage/node/abc/node_abc.hpp"

#include "quicklist.hpp"

#define JAGE_SCENE_ACTOR_ARGS std::string name, jage::Tag tag

namespace jage::node {

    namespace actor {
        class Camera;
    }

    /// \brief          The main container for every Actor node
    /// \details        This is the main or "root" node of every Hierarchy
    class Scene : public node::abc::NodeABC<actor::abc::ActorABC> {
    public:
        class TagIterator;

        Scene();

        template<class T>
        T* addChild(JAGE_SCENE_ACTOR_ARGS);
        template<class T, class... Args>
        T* addChild(JAGE_SCENE_ACTOR_ARGS, Args&&... args);

        /// \brief          Returns the QuickList of Volatile Actors
        [[nodiscard]] Utility::QuickList<std::shared_ptr<actor::abc::ActorABC>> getVolatileChildren() const;

        /// \brief          Creates a new Volatile Child under this Parent Actor
        /// \details        A Volatile Actor list is faster than a Hierarchy, preferred to be used whenever something
        ///                 needs to be spawned and destroyed frequently.
        /// \tparam T       The type of Actor (must be a subclass of <b>ActorBase</b>)
        /// \param name     Name of the Actor node
        /// \return         A pointer to the newly created Actor
        template<class T>
        T* addVolatileChild(JAGE_SCENE_ACTOR_ARGS);
        /// \brief          Creates a new Volatile Child under this Parent Actor
        /// \details        A Volatile Actor list is faster than a Hierarchy, preferred to be used whenever something
        ///                 needs to be spawned and destroyed frequently.
        /// \tparam T       The type of Actor (must be a subclass of <b>ActorBase</b>)
        /// \param name     Name of the Actor node
        /// \param args     The list of extra arguments to pass when creating the Actor
        /// \return         A pointer to the newly created Actor
        template<class T, class... Args>
        T* addVolatileChild(JAGE_SCENE_ACTOR_ARGS, Args&&... args);

        void tagActorToMap(const std::shared_ptr<actor::abc::ActorABC>& actor);

        TagIterator beginTagged(Tag tag);
        TagIterator endTagged(Tag tag);

        void update();
        void draw(jage::graphics::Shader &shader);

    protected:
        [[nodiscard]] std::string getTypeName() const override;

    private:
        /// Pre-set name of Scene's Hierarchy name
        static std::string m_hierarchyDisplayName;

        /// QuickList of Volatile Actors
        Utility::QuickList<std::shared_ptr<actor::abc::ActorABC>> m_volatileActors;

        std::vector<std::vector<std::weak_ptr<actor::abc::ActorABC>>> m_taggedMap;

        using jage::node::abc::NodeABC<jage::node::actor::abc::ActorABC>::addChild;
    };

    class Scene::TagIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = jage::node::actor::StaticActor*;
        using pointer           = jage::node::actor::StaticActor*;
        using reference         = jage::node::actor::StaticActor*;

        typedef std::vector<std::weak_ptr<actor::abc::ActorABC>> InternalType;

        TagIterator(InternalType::iterator iter, InternalType& original);

        reference operator*();
        pointer operator->();

        TagIterator& operator++();
        TagIterator operator++(int);

        bool operator== (const TagIterator& other);
        bool operator!= (const TagIterator& other);

    protected:
        InternalType::iterator m_iter;
        InternalType& m_original;

        void moveTillMatch();
    };
}

#include "jage/node/scene_impl.tpp"

#endif //JAGE_SCENE_HPP
