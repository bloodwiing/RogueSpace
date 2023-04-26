#include <gtest/gtest.h>
#include <gmock/gmock-actions.h>

#include "graphics/window.hpp"
#include "graphics/shader.hpp"

#include "utils.hpp"

TEST(Shader, LoadCompilable) {
    return;  // Disable test due to missing Headless X11 support

    ASSERT_NO_THROW(Utility::initializeOpenGL());

    using namespace Graphics;

    Window window(100, 100);
    window.activate();

    ASSERT_NO_THROW(Shader shader("./testres/compilable1.vert", "./testres/compilable1.frag"));
}

TEST(Shader, LoadNotCompilable) {
    return;  // Disable test due to missing Headless X11 support

    ASSERT_NO_THROW(Utility::initializeOpenGL());

    using namespace Graphics;

    Window window(100, 100);
    window.activate();

    EXPECT_THROW(Shader shader("./testres/uncompilable1.vert", "./testres/uncompilable1.frag"), std::runtime_error);

    EXPECT_THROW(Shader shader("./testres/uncompilable1.vert", "./testres/compilable1.frag"), std::runtime_error);

    EXPECT_THROW(Shader shader("./testres/compilable1.vert", "./testres/uncompilable1.frag"), std::runtime_error);
}