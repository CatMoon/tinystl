#ifndef SET_H
#define SET_H

#include "alloc.h"
#include "pair.h"
#include "rbtree.h"

namespace tinystl {

    template<typename Key, typename Compare=Less<Key>, typename _Alloc=Alloc>
    class Set {
    public:
        using KeyType = Key;
        using ValueType = Key;
        using SizeType = std::size_t;
        using DifferenceType = std::ptrdiff_t;
        using KeyCompare = Compare;
        using ValueCompare = Compare;

        using Reference = ValueType&;
        using ConstReference = const ValueType&;
        using Pointer = ValueType*;
        using ConstPointer = const ValueType*;

    protected:
        struct _KeyOfValue {
            const KeyType& operator()(const ValueType &value) const {
                return value;
            }
        };
        using _Container = RBTree<KeyType, ValueType, _KeyOfValue,
                                  Compare, _Alloc>;
    private:
        using __Self = Set<Key, Compare, _Alloc>;

    public:
        using Iterator = typename _Container::Iterator;
        using ConstIterator = typename _Container::ConstIterator;
        using ReverseIterator = typename _Container::ReverseIterator;
        using ConstReverseIterator = typename _Container::ConstReverseIterator;

        Set() = default;
        explicit Set(const Compare &compare): __container(compare) {}
        template<typename InputIterator>
        Set(InputIterator first, InputIterator last,
            const Compare &compare = Compare()): __container(compare) {
            __container.insertUnique(first, last);
        }
        Set(const __Self&) = default;
        __Self& operator=(const __Self &other) = default;

        Iterator begin() { return __container.begin(); }
        ConstIterator begin() const { return __container.begin(); }
        ConstIterator cbegin() const { return __container.cbegin(); }
        Iterator end() { return __container.end(); }
        ConstIterator end() const { return __container.end(); }
        ConstIterator cend() const { return __container.cend(); }
        ReverseIterator rbegin() { return __container.rbegin(); }
        ConstReverseIterator rbegin() const { return __container.rbegin(); }
        ConstReverseIterator crbegin() const { return __container.crbegin(); }
        ReverseIterator rend() { return __container.rend(); }
        ConstReverseIterator rend() const { return __container.rend(); }
        ConstReverseIterator crend() const { return __container.crend(); }

        bool empty() const { return __container.empty(); }
        SizeType size() const { return __container.size(); }
        SizeType maxSize() const { return __container.maxSize(); }
        void clear() { __container.clear(); }

        Pair<Iterator, bool> insert(const ValueType &value) {
            return __container.insertUnique(value); }
        Iterator insert(ConstIterator pos, const ValueType &value) {
            return __container.__insertUnique(pos.removeConst(), value);
        }
        template<typename InputIterator>
        void insert(InputIterator first, InputIterator last) {
            __container.insertUnique(first, last);
        }

        void erase(Iterator pos) { __container.erase(pos); }
        void erase(ConstIterator pos) { __container.erase(pos.removeConst()); }
        void erase(Iterator first, Iterator last) {
            __container.erase(first, last);
        }
        SizeType erase(const KeyType &key) {
            return __container.erase(key);
        }

        void swap(__Self &other) {
            using tinystl::swap;
            swap(__container, other.__container);
        }

        SizeType count(const KeyType &key) const {
            return __container.count(key);
        }

        Iterator find(const KeyType &key) {
            return __container.find(key);
        }
        ConstIterator find(const KeyType &key) const {
            return __container.find(key);
        }

        Iterator lowBound(const KeyType &key) {
            return __container.lowBound(key);
        }
        ConstIterator lowBound(const KeyType &key) const {
            return __container.lowBound(key);
        }
        Iterator upperBound(const KeyType &key) {
            return __container.upperBound(key);
        }
        Iterator upperBound(const KeyType &key) const {
            return __container.upperBound(key);
        }

        Pair<Iterator, Iterator> equalRange(const KeyType &key) {
            return __container.equalRange(key);
        }
        Pair<ConstIterator, ConstIterator> equalRange(const KeyType &key) const {
            return __container.equalRange(key);
        }

        template<typename Key1, typename Compare1, typename _Alloc1>
        friend bool operator==(const Set<Key1, Compare1, _Alloc1> &lhs,
                               const Set<Key1, Compare1, _Alloc1> &rhs);
        template<typename Key1, typename Compare1, typename _Alloc1>
        friend bool operator<(const Set<Key1, Compare1, _Alloc1> &lhs,
                             const Set<Key1, Compare1, _Alloc1> &rhs);

    private:
        _Container __container;
    };

    template<typename Key, typename Compare, typename _Alloc>
    inline bool operator==(const Set<Key, Compare, _Alloc> &lhs,
                           const Set<Key, Compare, _Alloc> &rhs) {
        return lhs.__container == rhs.__container;
    }

    template<typename Key, typename Compare, typename _Alloc>
    inline bool operator!=(const Set<Key, Compare, _Alloc> &lhs,
                           const Set<Key, Compare, _Alloc> &rhs) {
        return !(lhs == rhs);
    }

    template<typename Key, typename Compare, typename _Alloc>
    inline bool operator<(const Set<Key, Compare, _Alloc> &lhs,
                          const Set<Key, Compare, _Alloc> &rhs) {
        return lhs.__container < rhs.__container;
    }

    template<typename Key, typename Compare, typename _Alloc>
    inline bool operator>(const Set<Key, Compare, _Alloc> &lhs,
                          const Set<Key, Compare, _Alloc> &rhs) {
        return rhs < lhs;
    }

    template<typename Key, typename Compare, typename _Alloc>
    inline bool operator<=(const Set<Key, Compare, _Alloc> &lhs,
                           const Set<Key, Compare, _Alloc> &rhs) {
        return !(rhs < lhs);
    }

    template<typename Key, typename Compare, typename _Alloc>
    inline bool operator>=(const Set<Key, Compare, _Alloc> &lhs,
                           const Set<Key, Compare, _Alloc> &rhs) {
        return !(lhs < rhs);
    }

}

#endif
