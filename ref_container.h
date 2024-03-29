
#pragma once

#include <memory>


#define REF_CONTAINER_KV(CONTAINER, K, V) ref_container<CONTAINER<K, std::shared_ptr<V>>, K, V>
#define REF_CONTAINER(CONTAINER, V) ref_container<CONTAINER<std::shared_ptr<V>>, CONTAINER<std::shared_ptr<V>>::size_type, V>

template <class container, typename K, typename V>
class ref_container : public container
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

        friend class ref_container;

    public:
        V* operator->()
        {
            return _it->get();
        }
        V& operator*()
        {
            return *_it->get();
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

        friend class ref_container;

    public:
        const V* operator->()
        {
            return _it->get();
        }
        const V& operator*()
        {
            return *_it->get();
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

    typedef iterator_<typename container::iterator> ref_iterator;
    typedef const_iterator_<typename container::const_iterator> ref_const_iterator;

public:
    ref_iterator begin()
    {
        return ref_iterator(container::begin());
    }

    ref_const_iterator begin() const
    {
        return ref_const_iterator(container::cbegin());
    }

    ref_const_iterator cbegin() const noexcept
    {
        return ref_const_iterator(container::cbegin());
    }

    ref_iterator end()
    {
        return ref_iterator(container::end());
    }

    ref_const_iterator end() const
    {
        return ref_const_iterator(container::cend());
    }

    ref_const_iterator cend() const noexcept
    {
        return ref_const_iterator(container::cend());
    }

    V& operator[](const K& k)
    {
        return *(container::at(k).get());
    }

    V& at(const K& k)
    {
        return *(container::at(k).get());
    }

    const V& at(const K& k) const
    {
        return *(container::at(k).get());
    }

    V* get(const K& k)
    {
        return container::at(k).get();
    }

    const V* get(const K& k) const
    {
        return container::at(k).get();
    }

    std::shared_ptr<V>& at_base(const K& k)
    {
        return container::at(k);
    }

    const std::shared_ptr<V>& at_base(const K& k) const
    {
        return container::at(k);
    }

#if REF_CONTAINER_FRONT
    V& front()
    {
        return *container::front().get();
    }

    const V& front() const
    {
        return *container::front().get();
    }

    V* get_front()
    {
        return container::front().get();
    }

    const V* get_front() const
    {
        return container::front().get();
    }

    std::shared_ptr<V>& front_base()
    {
        return container::front();
    }

    const std::shared_ptr<V>& front_base() const
    {
        return container::front();
    }
#endif  // REF_CONTAINER_FRONT

#if REF_CONTAINER_BACK
    V& back()
    {
        return *container::back().get();
    }

    const V& back() const
    {
        return *container::back().get();
    }

    V* get_back()
    {
        return container::back().get();
    }

    const V* get_back() const
    {
        return container::back().get();
    }

    std::shared_ptr<V>& back_base()
    {
        return container::back();
    }

    const std::shared_ptr<V>& back_base() const
    {
        return container::back();
    }
#endif  // REF_CONTAINER_BACK
};
