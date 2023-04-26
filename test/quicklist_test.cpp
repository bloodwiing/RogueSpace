#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>
#include <algorithm>

#include "quicklist.hpp"

using namespace testing;

TEST(QuickList, AddingElements) {
    using Utility::QuickList;

    QuickList<int> list(16);

    ASSERT_EQ(list.getSize(), 0);
    ASSERT_THAT(std::vector<int>(list.begin(), list.end()), ElementsAreArray(std::vector<int>{}));

    list.add(10);
    ASSERT_EQ(list.getSize(), 1);
    ASSERT_THAT(std::vector<int>(list.begin(), list.end()), ElementsAreArray(std::vector<int>{10}));

    list.add(1);
    list.add(2);
    ASSERT_EQ(list.getSize(), 3);
    ASSERT_THAT(std::vector<int>(list.begin(), list.end()), ElementsAreArray(std::vector<int>{2, 1, 10}));
}

TEST(QuickList, AccessingElements) {
    using Utility::QuickList;

    QuickList<int> list;

    auto index_15 = list.add(15);
    auto index_5 = list.add(5);
    auto index_10 = list.add(10);

    ASSERT_EQ(list.get(index_5), 5);
    ASSERT_EQ(list.get(index_10), 10);
    ASSERT_EQ(list.get(index_15), 15);

    ASSERT_THAT(std::vector<int>(list.begin(), list.end()), ElementsAreArray(std::vector<int>{10, 5, 15}));
}

TEST(QuickList, RemovingElements) {
    using Utility::QuickList;

    QuickList<char> list;

    auto index_a = list.add('a');
    auto index_b = list.add('b');
    auto index_c = list.add('c');

    ASSERT_EQ(list.getSize(), 3);
    ASSERT_THAT(std::vector<char>(list.begin(), list.end()), ElementsAreArray(std::vector<char>{'c', 'b', 'a'}));

    list.remove(index_b);

    ASSERT_EQ(list.getSize(), 2);
    ASSERT_THAT(std::vector<char>(list.begin(), list.end()), ElementsAreArray(std::vector<char>{'c', 'a'}));

    auto index_d = list.add('d');
    auto index_e = list.add('e');

    ASSERT_EQ(list.getSize(), 4);
    ASSERT_THAT(std::vector<char>(list.begin(), list.end()), ElementsAreArray(std::vector<char>{'e', 'd', 'c', 'a'}));

    list.remove(index_a);

    ASSERT_EQ(list.getSize(), 3);
    ASSERT_THAT(std::vector<char>(list.begin(), list.end()), ElementsAreArray(std::vector<char>{'e', 'd', 'c'}));

    list.remove(index_e);

    ASSERT_EQ(list.getSize(), 2);
    ASSERT_THAT(std::vector<char>(list.begin(), list.end()), ElementsAreArray(std::vector<char>{'d', 'c'}));

    list.remove(index_c);
    list.remove(index_d);

    ASSERT_EQ(list.getSize(), 0);
    ASSERT_THAT(std::vector<char>(list.begin(), list.end()), ElementsAreArray(std::vector<char>{}));
}

TEST(QuickList, ExpandingCapacity) {
    using Utility::QuickList;

    QuickList<char> list(5);

    ASSERT_EQ(list.getCapacity(), 5);

    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);

    ASSERT_EQ(list.getCapacity(), 5);

    auto index_5 = list.add(5);

    ASSERT_EQ(list.getCapacity(), 10);

    list.remove(index_5);

    ASSERT_EQ(list.getCapacity(), 10);
}

TEST(QuickList, ToString) {
    using Utility::QuickList;

    QuickList<std::string> list;

    list.add("Apple");
    auto index_orange = list.add("Orange");
    list.add("Banana");

    ASSERT_EQ(list.toString(), std::string("<QuickList { Banana, Orange, Apple, }>"));

    list.remove(index_orange);

    ASSERT_EQ(list.toString(), std::string("<QuickList { Banana, Apple, }>"));

    list.add("Kiwi");
    list.add("Orange");

    ASSERT_EQ(list.toString(), std::string("<QuickList { Orange, Kiwi, Banana, Apple, }>"));
}

TEST(QuickList, Iterator) {
    using Utility::QuickList;

    QuickList<int> list;

    list.add(1000);
    list.add(100);
    list.add(10);

    ASSERT_EQ(*(list.begin()), 10);
    ASSERT_EQ(*(++list.begin()), 100);
    ASSERT_EQ(*(++(++list.begin())), 1000);

    ASSERT_EQ(++(++(++list.begin())), list.end());
}

TEST(QuickList, IteratorAlgorithms) {
    using Utility::QuickList;

    QuickList<int> list;

    list.add(111);
    list.add(222);
    list.add(333);
    list.add(444);

    ASSERT_THAT(std::vector<int>(list.begin(), list.end()), ElementsAreArray(std::vector<int>{444, 333, 222, 111}));

    std::for_each(list.begin(), list.end(), [](int& val) { val += 111; });

    ASSERT_THAT(std::vector<int>(list.begin(), list.end()), ElementsAreArray(std::vector<int>{555, 444, 333, 222}));

    for (auto iter = list.begin(); iter != list.end(); ++iter) {
        *(iter) -= 222;
    }

    ASSERT_THAT(std::vector<int>(list.begin(), list.end()), ElementsAreArray(std::vector<int>{333, 222, 111, 0}));

    for (int& iter : list) {
        iter *= 2;
    }

    ASSERT_THAT(std::vector<int>(list.begin(), list.end()), ElementsAreArray(std::vector<int>{666, 444, 222, 0}));
}

TEST(QuickList, SafeRemove) {
    using Utility::QuickList;

    QuickList<int> list;

    list.add(321);
    list.add(654);
    list.add(987);

    ASSERT_THAT(std::vector<int>(list.begin(), list.end()), ElementsAreArray(std::vector<int>{987, 654, 321}));

    for (auto iter = list.begin(); iter != list.end(); ++iter) {
        if (*iter < 900)
            iter.safeRemove();
    }

    ASSERT_THAT(std::vector<int>(list.begin(), list.end()), ElementsAreArray(std::vector<int>{987}));
}