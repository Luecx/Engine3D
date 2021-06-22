//
// Created by Luecx on 15.06.2021.
//

#ifndef ECS_ECS_ECS_H_
#define ECS_ECS_ECS_H_

#include "component.h"
#include "entity.h"
#include "event.h"
#include "hash.h"
#include "iterator.h"
#include "system.h"
#include "types.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <vector>

namespace ecs {

struct ECS : public System {
    std::unordered_map<Hash, std::vector<Entity*>>            componentEntityList {};
    std::vector<Entity*>                                      entities {};
    std::vector<System*>                                      systems {};
    std::unordered_map<Hash, std::vector<EventBaseListener*>> eventListener {};

    friend Entity;

    virtual ~ECS() { destroyAll(); }

    Entity* spawn() {
        Entity* entity   = new Entity(this);
        entity->entityID = entities.size();
        entities.push_back(entity);
        return entity;
    }
    void shrinkIndices() {
        // remove all elements with an invalid ID -> has been removed previously
        entities.erase(
            std::remove_if(entities.begin(), entities.end(),
                           [](const Entity* o) { return o == nullptr || o->entityID == INVALID_ID; }),
            entities.end());

        // renumber entities
        for (int i = 0; i < entities.size(); i++) {
            entities[i]->entityID = i;
        }
    }

    private:
    void componentRemoved(Hash hash, Entity* entity) {
        const ID entityID = entity->entityID;
        componentEntityList[hash].erase(
            std::remove_if(componentEntityList[hash].begin(), componentEntityList[hash].end(),
                           [&entityID](const Entity* o) {
                               return o->entityID == entityID || o->entityID == INVALID_ID;
                           }),
            componentEntityList[hash].end());
    }
    template<typename C> void componentRemoved(Entity* entity) {
        Hash hash = getComponentHash<C>();
        componentRemoved(hash, entity);
    }
    template<typename C> void componentAdded(Entity* entity) {
        Hash hash = getComponentHash<C>();
        componentEntityList[hash].push_back(entity);
    }

    public:
    void destroy(ID id) {
        if (id == INVALID_ID || id >= entities.size())
            return;
        if (entities[id] == nullptr)
            return;

        // deallocate the entity
        delete entities[id];
        // this also called the deallocation for the components
        entities[id] = nullptr;
    }
    void destroy(Entity* entity) {
        if(entity == nullptr) return;
        destroy(entity->entityID);
    }
    void destroyAll() {
        for (Entity*& en : entities) {
            destroy(en);
        }
        entities.clear();
    }
    template<typename K, typename... R> EntitySubSet<K, R...> each() {
        return EntitySubSet<K, R...> {&componentEntityList[getComponentHash<K>()]};
    }
    template<typename K, typename...R> Entity* first(){
        for(Entity* entity:componentEntityList[getComponentHash<K>()]){
            if(entity->has<K,R...>()){
                return entity;
            }
        }
        return nullptr;
    }

    template<typename Event> void              addEventListener(EventListener<Event>* listener) {
        // check if there already exists an event listener of the same kind
        Hash hash = getComponentHash<Event>();
        if (eventListener.find(hash) == eventListener.end()) {
            eventListener[hash] = {};
        }
        eventListener[hash].push_back(listener);
    }
    template<typename Event> void emitEvent(const Event& event) {
        Hash hash = getComponentHash<Event>();
        if (eventListener.find(hash) == eventListener.end())
            return;
        for (EventBaseListener* listener : eventListener[hash]) {
            auto l = reinterpret_cast<EventListener<Event>*>(listener);
            l->receive(event);
        }
    }
    void addSystem(System* system) {
        systems.push_back(system);
    }
    void process(double delta) {
        for (System* sys : systems) {
            sys->process(this, delta);
        }
    }
    void process(ECS* ecs, double delta) override {
        for (System* sys : systems) {
            sys->process(ecs, delta);
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const ECS& ecs1) {

        for(const auto& h:ecs1.componentEntityList){
            os << "key=" << std::setw(20) << h.first.hash_code() << "  ";
            for(auto k:h.second){
                os << " | " << std::setw(10) << k;
            }
            os << std::endl;
        }
        return os;
    }
};

}    // namespace ecs

#endif    // ECS_ECS_ECS_H_
