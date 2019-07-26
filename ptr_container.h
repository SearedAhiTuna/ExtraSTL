
#pragma once

#include <memory>


#define PTR_CONTAINER_KV(CONTAINER, K, V) ptr_container<CONTAINER<K, std::shared_ptr<V>>, K, V>
#define PTR_CONTAINER(CONTAINER, V) ptr_container<CONTAINER<std::shared_ptr<V>>, CONTAINER<std::shared_ptr<V>>::size_type, V>

template <class container, typename K, typename V>
class ptr_container : public container
{
public:
    template <class base_iterator>
    class iterator_
    {
    private:
        iterator_(const base_iterator& it) :
            _it(it)
        {
        }

        friend class ptr_container;

    public:
        V* operator*()
        {
            return _it->get();
        }

        iterator_& operator++()
        {
            ++_it;
            return *this;
        }

        bool operator!=(const iterator_& other)
        {
            return _it != other._it;
        }

    private:
        base_iterator _it;
    };

    template <class base_const_iterator>
    class const_iterator_
    {
    private:
        const_iterator_(const base_const_iterator& it) :
            _it(it)
        {
        }

        friend class ptr_container;

    public:
        const V* operator*()
        {
            return _it->get();
        }

        const_iterator_& operator++()
        {
            ++_it;
            return *this;
        }

        bool operator!=(const const_iterator_& other)
        {
            return _it != other._it;
        }

    private:
        base_const_iterator _it;
    };

    typedef iterator_<typename container::iterator> ptr_iterator;
    typedef const_iterator_<typename container::const_iterator> ptr_const_iterator;

public:
    ptr_iterator begin()
    {
        return ptr_iterator(container::begin());
    }

    ptr_const_iterator begin() const
    {
        return ptr_const_iterator(container::cbegin());
    }

    ptr_const_iterator cbegin() const noexcept
    {
        return ptr_const_iterator(container::cbegin());
    }

    ptr_iterator end()
    {
        return ptr_iterator(container::end());
    }

    ptr_const_iterator end() const
    {
        return ptr_const_iterator(container::cend());
    }

    ptr_const_iterator cend() const noexcept
    {
        return ptr_const_iterator(container::cend());
    }

    V* operator[](const K& k)
    {
        return container::at(k).get();
    }

    V* at(const K& k)
    {
        return container::at(k).get();
    }

    const V* at(const K& k) const
    {
        return container::at(k).get();
    }

    std::shared_ptr<V> at_base(const K& k)
    {
        return container::at(k);
    }

    const std::shared_ptr<V> at_base(const K& k) const
    {
        return container::at(k);
    }
};