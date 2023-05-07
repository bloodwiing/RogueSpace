#include "jage/script/abc/script_abc.hpp"

jage::script::abc::ScriptABC::AttachError::AttachError()
    : std::invalid_argument("Could not attach to Actor - invalid type")
{ }
