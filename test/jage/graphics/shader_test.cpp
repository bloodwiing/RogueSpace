#include "jage/graphics/shader.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock-actions.h>

#include "jage/runtime/window.hpp"
#include "jage/utility/utility.hpp"

using jage::graphics::Shader;

TEST(Shader, LoadCompilable) {
    return;  // Disable test due to missing Headless X11 support

    ASSERT_NO_THROW(jage::utility::initializeOpenGL());

    using namespace jage::runtime;

    Window window(100, 100);
    window.activate();

    ASSERT_NO_THROW(Shader shader("./testres/compilable1.vert", "./testres/compilable1.frag"));
}

TEST(Shader, LoadNotCompilable) {
    return;  // Disable test due to missing Headless X11 support

    ASSERT_NO_THROW(jage::utility::initializeOpenGL());

    using namespace jage::runtime;

    Window window(100, 100);
    window.activate();

    EXPECT_THROW(Shader shader("./testres/uncompilable1.vert", "./testres/uncompilable1.frag"), std::runtime_error);

    EXPECT_THROW(Shader shader("./testres/uncompilable1.vert", "./testres/compilable1.frag"), std::runtime_error);

    EXPECT_THROW(Shader shader("./testres/compilable1.vert", "./testres/uncompilable1.frag"), std::runtime_error);
}