#include "jage/node/frame/abc/frame_abc.hpp"

using jage::node::frame::abc::FrameABC;

FrameABC::FrameABC(JAGE_FRAME_ARGS)
    : node::abc::NodeABC<FrameABC>(parent, std::move(name))
    , m_canvas(canvas)
{

}
