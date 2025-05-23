#ifndef JAGE_TAGS_HPP
#define JAGE_TAGS_HPP

#include "jage/utility/utility.hpp"

namespace jage {

    enum Tag {
        UNTAGGED,
        SYSTEM,

        ENVIRONMENT,
        CAMERA,
        MESH,
        UI,

        PLAYER,
        ENEMY,

        BULLET,
    };
}

template<>
struct jage::utility::EnumSize<jage::Tag> {
    static const size_t value = Tag::BULLET + 1;
};

#endif //JAGE_TAGS_HPP
