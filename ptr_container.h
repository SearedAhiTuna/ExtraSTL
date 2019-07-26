
#pragma once

#include <memory>

#define PTR_CONTAINER(CONTAINER, T) ptr_container<CONTAINER<std::shared_ptr<T>>, T>
#define PTR_CONTAINER_KV(CONTAINER, K, V) ptr_container<CONTAINER<K, std::shared_ptr<V>>, V>

template <class container, typename K, typename T>
class ptr_container : public container
{
public:
    class iterator
    {
    private:
        iterator(container::iterator& it) :
            _it(it)
        {
        }

        friend class ptr_container;

    public:
        T* operator->()
        {
            return _it->get();
        }
        T& operator*()
        {
            return *_it->get();
        }

        iterator& operator++()
        {
            ++_it;
            return *this;
        }

        bool operator!=(const iterator& other)
        {
            return _it != other._it;
        }

    private:
        container::iterator& _it;
    };

    class const_iterator
    {
    private:
        const_iterator(container::const_iterator& it) :
            _it(it)
        {
        }

        friend class ptr_container;

    public:
        const T* operator->()
        {
            return _it->get();
        }
        const T& operator*()
        {
            return *_it->get();
        }

        const_iterator& operator++()
        {
            ++_it;
            return *this;
        }

        bool operator!=(const const_iterator& other)
        {
            return _it != other._it;
        }

    private:
        container::const_iterator& _it;
    };

public:
    iterator begin()
    {
        return iterator(container::begin());
    }

    const_iterator begin() const
    {
        return const_iterator(container::cbegin());
    }

    const_iterator cbegin() const noexcept
    {
        return const_iterator(container::cbegin());
    }

    iterator end()
    {
        return iterator(container::end());
    }

    const_iterator end() const
    {
        return const_iterator(container::cend());
    }

    const_iterator cend() const noexcept
    {
        return const_iterator(container::cend());
    }

    T& operator[](const K& k)
    {
        return *container::at(k)->get();
    }
    
    T& at(const K& k)
    {
        return *container::at(k)->get();
    }

    const T& at(const K& k) const
    {
        return *container::at(k)->get();
    }
};
