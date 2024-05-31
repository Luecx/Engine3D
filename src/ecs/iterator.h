//
// Created by Luecx on 16.06.2021.
//

#ifndef ECS_ECS_ITERATOR_H_
#define ECS_ECS_ITERATOR_H_

#include "entity.h"
#include "types.h"

#include <vector>

namespace ecs {

template<typename... RTypes>
struct EntityIterator {

    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = Entity*;
    using pointer           = value_type*;    // or also value_type*
    using reference         = value_type&;    // or also value_type&

    reference operator*() const {
        return *m_ptr;
    }
    pointer operator->() {
        return m_ptr;
    }

    EntityIterator(pointer p_ptr, pointer p_end)
        : m_ptr(p_ptr)
        , m_end(p_end) {

        while (p_ptr != p_end
               && (*p_ptr == nullptr || (*p_ptr != nullptr && !(*p_ptr)->has<RTypes...>()))) {
            p_ptr++;
        }
        this->m_ptr = p_ptr;
    }

    // Prefix increment
    EntityIterator<RTypes...>& operator++() {
        m_ptr++;
        if (m_ptr == m_end)
            return *this;
        while (m_ptr != m_end
               && (*m_ptr == nullptr || (*m_ptr != nullptr && !(*m_ptr)->has<RTypes...>()))) {
            m_ptr++;
        }
        return *this;
    }

    bool operator==(const EntityIterator<RTypes...>& rhs) const {
        return m_ptr == rhs.m_ptr;
    }
    bool operator!=(const EntityIterator<RTypes...>& rhs) const {
        return !(rhs == *this);
    }

    friend std::ostream& operator<<(std::ostream& os, const EntityIterator& iterator) {
        os << "m_ptr: " << iterator.m_ptr;
        return os;
    }

    private:
    pointer m_ptr;
    pointer m_end;
};

template<typename... RTypes>
struct EntitySubSet {
    std::vector<Entity*>* entities {};

    EntitySubSet(std::vector<Entity*>* p_entities)
        : entities(p_entities) {}

    EntityIterator<RTypes...> begin() {
        return EntityIterator<RTypes...> {entities->begin().base(), entities->end().base()};
    }
    EntityIterator<RTypes...> end() {
        return EntityIterator<RTypes...> {entities->end().base(), entities->end().base()};
    }
};

}    // namespace ecs

#endif    // ECS_ECS_ITERATOR_H_
