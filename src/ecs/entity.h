//
// Created by Luecx on 16.06.2021.
//

#include <unordered_map>
#include "types.h"
#include "hash.h"

#ifndef ECS_ECS_ENTITY_H_
#define ECS_ECS_ENTITY_H_

namespace ecs {

struct Entity {
    private:
    ID                                                entityID;

    std::unordered_map<Hash, ComponentBaseContainer*> components {};
    ECS*                                              ecs;

    friend ECS;

    public:
    Entity(ECS* p_ecs) { this->ecs = p_ecs; }
    virtual ~Entity() { removeAll(); }

    template<typename T> bool has() {
        Hash hash = getComponentHash<T>();
        return components.find(hash) != components.end();
    }
    template<typename T, typename V, typename... Types> bool has() {
        return has<T>() && has<V, Types...>();
    }
    template<typename T> ComponentContainer<T>& get() {
        static ComponentContainer<T> emptyContainer {};
        if (entityID == INVALID_ID)
            return emptyContainer;
        Hash hash = getComponentHash<T>();
        if (components.find(hash) != components.end()) {
            return *reinterpret_cast<ComponentContainer<T>*>(components.at(hash));
        }
        return emptyContainer;
    }
    template<typename T, typename... Args> void assign(Args&&... args);
    template<typename T> void                   remove();
    void                                        removeAll();
    void                                        destroy();
    ID                                          getEntityId() const { return entityID; }

    bool operator==(const Entity& rhs) const { return entityID == rhs.entityID; }
    bool operator!=(const Entity& rhs) const { return !(rhs == *this); }
    bool operator<(const Entity& rhs) const { return entityID < rhs.entityID; }
    bool operator>(const Entity& rhs) const { return rhs < *this; }
    bool operator<=(const Entity& rhs) const { return !(rhs < *this); }
    bool operator>=(const Entity& rhs) const { return !(*this < rhs); }
};


}    // namespace ecs

#endif    // ECS_ECS_ENTITY_H_