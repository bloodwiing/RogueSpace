/// <h1>QuickList</h1>



/// <h3>ABOUT</h3>
/// <p>
/// <b>QuickList</b><br>
/// <i>Copyright (c) BLOODWIING (Donatas Kirda) 2023</i><br>
/// A list that can be quickly accessed, read and written without the concept of data being ordered.<br>
/// Implemented by mixing a dynamic array with a double linked list together.<br><br>
/// </p>



/// <h3>TIME COMPLEXITY (Worst case)</h3>
/// <ul>
/// <li>Write - O(n)</li
/// <li>Read - O(1)</li
/// <li>Delete - O(1)</li
/// </ul>



/// <h3>TIME COMPLEXITY (Standard case)</h3>
/// <ul>
/// <li>Write - O(1)</li
/// <li>Read - O(1)</li
/// <li>Delete - O(1)</li
/// </ul>



/// <h3>SPACE COMPLEXITY (Standard case)</h3>
/// <p>O(n)<br><br></p>

/// <h3>HOW IT WORKS</h3>
/// <p>
/// The list is a self-patching double linked list that elements exist in a single allocated heap.<br>
/// It stores its own size, capacity, the pointer to the start of the heap and a pointer to an element of the list called "nextFree".
/// <br><br>

/// Each element is a double linked list structure.
/// <br><br>

/// When a new element is added, it gets written to the pointer where nextFree points to.<br>
/// If the element does not have a pointer to the preceding element, it assumes that the next element is uninitialised
///     and makes the "nextFree" point to an element of index "size" also sets that pointed element to point backwards to
///     the element we just wrote.<br>
/// The new "nextFree" element is the next element (which was either already ready or just initialised).<br>
/// This also includes a capacity check, which will increase the reserved memory if the "size" is reaching the "capacity".
/// <br><br>

/// In case an element is deleted, 2 steps happen:<br>
/// <ol type="1">
/// <li>"nextFree" moves to be the element after the one we are removing<br>
///     Since elements behind "nextFree" are all taken, and elements after all all vacant. We can make our fresh slot we just
///     deleted be the new "nextFree" element and move the older one to the after it<br>
///     For this to work, we modify the "nextFree"'s back element's forward pointer to point the deleted slot,
///     "nextFree"'s back pointer to point to the deleted slot and the deleted element to point forwards to the previous "nextFree"
///     and backwards to the last taken slot.</li>
/// <li>The linked list gets patched.<br>
///     The element that gets removed passes its previous and next element pointers to its next and previous elements respectively.<br>
///     Thus removing it from a Double Linked List.</li>
/// </ol>
/// <br><br>

/// This implementation cannot be ordered, there is no option to insert an element into a specific index in this list<br>
/// Therefore to access and identify elements, the add function returns the index of the "nextFree" element that was used
/// to write an element.<br>
/// Indices don't change even after copies or reserved space expansions, they are static until the element is removed and the
/// index is marked vacant - that's when a new element can be written to it
/// <br><br>

/// All in all this list is super helpful to manage an arbitrary-sized list of volatile values, which are expected to be added
/// and removed frequently.
/// </p>

#ifndef QUICK_LIST_HPP
#define QUICK_LIST_HPP

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <algorithm>

namespace Utility {

    /// A non-sorted quick write and deletion array.
    /// \tparam T The type of objects to store
    template<class T>
    class QuickList {
    public:

        typedef size_t index_t;
        /// Value Type
        typedef T value_type;

        /// QuickList constructor.<br>
        /// Automatically manages the list entries
        /// \param chunkSize The size of a chunk of elements. The List expands by this increment
        explicit QuickList(size_t chunkSize = 8)
                : chunkSize(chunkSize)
                , capacity(chunkSize)
                , size(0)
                , entries(chunkSize)
                , nextFree(0)
        { }
        /// QuickList Copy constructor.<br>
        /// Creates a copy of the already existing list
        /// \param ref A reference to the constructor to copy
        QuickList(const QuickList<T>& ref)
                : chunkSize(ref.chunkSize)
                , capacity(ref.capacity)
                , size(ref.size)
                , entries(ref.entries)
                , nextFree(ref.nextFree)
        { }

        /// Insert an element into the QuickList.<br>
        /// To access this element in the list, please use the returned index, which is picked vacant
        /// and cannot be chosen manually
        /// \param value The value of the element to insert
        /// \return The reserved index of the value
        index_t add(const T& value) {
            expandIfNeeded();

            Entry& targetElem = entries[nextFree];
            index_t targetIndex = nextFree;

            // next free slot has been untouched (has all zero values)
            if (targetElem.next == -1) {
                targetElem.next = nextFree + 1;
                entries[targetElem.next].prev = nextFree;
            }

            targetElem.value = value;
            targetElem.busy = true;
            ++size;
            nextFree = targetElem.next;

            return targetIndex;
        }

        /// Read an element from the QuickList.<br>
        /// Needs a reserved index that is returned when inserting an element
        /// \param index The reserved index of the element
        /// \return The element stored in the QuickList
        [[nodiscard]] T& get(index_t index) {
            if (index >= entries.capacity())
                throw std::out_of_range("Index is out of bounds");

            if (!entries[index].busy)
                throw std::runtime_error("Index does not contain an element");

            return entries[index].value;
        }

        /// Removes an element from the QuickList.<br>
        /// Needs a reserved index that is returned when inserting an element<br>
        /// <i>Do not use in the middle of a loop or iterator as it will overwrite the order of the elements</i><br>
        /// <i>If you want to iterate over elements and remove them during an iteration, use the safeRemove() function of the iterator</i>
        /// \param index The reserved index of the element
        void remove(index_t index) {
            if (index >= entries.capacity())
                throw std::out_of_range("Index is out of bounds");

            Entry& targetElem = entries[index];
            Entry& nextFreeElem = entries[nextFree];

            if (!targetElem.busy)
                throw std::invalid_argument("Index does not contain an element");

            // if it's the last element, we can keep the current chain, but just start from the beginning of it
            if (targetElem.prev == -1 and size == 1) {
                targetElem.busy = false;
                --size;
                nextFree = index;
                return;
            }

            // insert a free slot in the chain (if it isn't already)
            index_t newPrev;
            if (nextFreeElem.prev != index) {
                entries[nextFreeElem.prev].next = index;
                newPrev = nextFreeElem.prev;
                nextFreeElem.prev = index;
            } else {
                newPrev = targetElem.prev;
            }

            // move the busy slot ouf of the chain
            if (targetElem.prev != -1)
                entries[targetElem.prev].next = targetElem.next;
            if (targetElem.next != -1)
                entries[targetElem.next].prev = targetElem.prev;
            targetElem.prev = newPrev;
            targetElem.next = nextFree;

            targetElem.busy = false;
            --size;

            nextFree = index;
        }

        /// Current reserved capacity of the QuickList.<br>
        /// A multiple of the chunkSize
        [[nodiscard]] index_t getCapacity() const {
            return capacity;
        }
        /// Count of elements stored in the QuickList.
        [[nodiscard]] index_t getSize() const {
            return size;
        }

    protected:
        struct Entry {
            T value;
            bool busy = false;
            index_t next = -1, prev = -1;
        };

    public:
        /// QuickList iterator.<br>
        /// Returns elements in the order they were added, first being newest, last - oldest
        class iterator;

        /// The start of the QuickList (latest element)
        iterator begin() {
            return iterator(entries[nextFree].prev, this);
        }

        /// The end of the QuickList (oldest element)
        iterator end() {
            return iterator(-1, this);
        }

        /// QuickList converter to a C++ String
        [[nodiscard]] std::string toString() {
            std::stringstream ss;
            ss << "<QuickList { ";
            std::for_each(begin(), end(), [&ss](T item) { ss << item << ", "; });
            ss << "}>";
            return ss.str();
        }

    private:
        std::vector<Entry> entries;  // Pointer to the memory reserved
        size_t capacity;  // The current maximum capacity
        size_t size;  // The

        index_t nextFree;  // Next entry of the QuickList that is vacant

        /// Helper function to increase the capacity if the QuickList is about to hit it
        void expandIfNeeded() {
            if (size + 1 >= capacity) {
                capacity += chunkSize;
                entries.resize(capacity, {});
            }
        }

        const size_t chunkSize;
    };

    template<class T>
    class QuickList<T>::iterator {
    private:
        index_t cur;
        QuickList* list;
        index_t toSafeRemove;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = index_t;
        using pointer = T*;
        using reference = T;

        explicit iterator(index_t cur, QuickList* list)
                : cur(cur)
                , list(list)
                , toSafeRemove(-1)
        { }

        iterator(const iterator &it)
                : cur(it.cur)
                , list(it.list)
                , toSafeRemove(it.toSafeRemove)
        { }

        iterator& operator++() {
            cur = list->entries[cur].prev;
            // After the element to removed has been passed, remove it as now it won't affect the element chain
            if (toSafeRemove != -1) {
                list->remove(toSafeRemove);
                toSafeRemove = -1;
            }
            return *this;
        }

        iterator operator++(int) {
            iterator retval = *this;
            ++(*this);
            return retval;
        }

        bool operator==(iterator other) const {
            return cur == other.cur;
        }

        bool operator!=(iterator other) const {
            return !(*this == other);
        }

        T& operator*() const {
            return list->entries[cur].value;
        }

        /// Built-in safe removal of an element after it was processed
        void safeRemove() {
            toSafeRemove = cur;
        }
    };

    template<class T>
    std::ostream& operator<<(std::ostream& stream, QuickList<T>& list) {
        stream << list.toString();
        return stream;
    }
}

#endif //QUICK_LIST_HPP
