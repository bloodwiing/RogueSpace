#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>

#include "utils.hpp"

using namespace testing;

TEST(Utils, readFileContents_TextFile) {
    using Utility::readFileContents;

    // Should be the file contents in the C++ string
    ASSERT_EQ(readFileContents("./testres/filecontents1.txt", std::ios::in), std::string(
            "FILE CONTENT TEST 1\n"
            "The contents of this file should be read into a C++ string\n"
            "This test is being asserted - it cannot fail\n"
            "\n"
            "If the test does fail, this would lead to a complete asset loading breakdown"));
}

TEST(Utils, readFileContents_InvalidFile) {
    using Utility::readFileContents;

    // Should be an empty string
    ASSERT_EQ(readFileContents("./testres/invalid.file", std::ios::in), std::string(""));
}

TEST(Utils, readFileContents_BinaryFile) {
    using Utility::readFileContents;

    // Data to compare against
    std::vector<uint8_t> data = {0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00,
                                 0x01, 0x23, 0x45, 0x67, 0x89, 0x98, 0x76, 0x54, 0x32, 0x10};
    // Should be equal to a C++ string equivalent of the binary data
    ASSERT_THAT(readFileContents("./testres/filecontents2.bin", std::ios::in | std::ios::binary), ElementsAreArray(data));
}

TEST(Utils, readFileContents_BinaryFileWithFakeEnding) {
    using Utility::readFileContents;

    // Data to compare against
    std::vector<uint8_t> data = {0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00,
                                 0x01, 0x23, 0x45, 0x67, 0x89, 0x98, 0x76, 0x54, 0x32, 0x10,
                                 'f', 'a', 'k', 'e', ' ', 'n', 'e', 'w', 'l', 'i', 'n', 'e',
                                 '\r', '\n', 0x69};
    // Should be equal to a C++ string equivalent of the binary data
    ASSERT_THAT(readFileContents("./testres/filecontents3.bin", std::ios::in | std::ios::binary), ElementsAreArray(data));
}

TEST(Utils, unixifyLineEndings) {
    using Utility::readFileContents;
    using Utility::unixifyLineEndings;

    std::string windowsEndings = "This is a test\r\n"
                                 "Of Windows style\r\n"
                                 "Line endings\r\n"
                                 "";

    std::string unixifiedEndings = "This is a test\n"
                                   "Of Windows style\n"
                                   "Line endings\n"
                                   "";

    std::string unixEndings = "This is a test\n"
                              "Of UNIX style\n"
                              "Line endings\n"
                              "";

    ASSERT_NE(windowsEndings, unixifiedEndings);

    unixifyLineEndings(windowsEndings);
    ASSERT_EQ(windowsEndings, unixifiedEndings);

    unixifyLineEndings(unixEndings);
    ASSERT_EQ(unixEndings, "This is a test\n"
                           "Of UNIX style\n"
                           "Line endings\n"
                           "");
}