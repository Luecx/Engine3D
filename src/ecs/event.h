//
// Created by Luecx on 16.06.2021.
//

#ifndef ECS_ECS_EVENT_H_
#define ECS_ECS_EVENT_H_

namespace ecs {

struct EventBaseListener {};

template<typename Event>
struct EventListener : public EventBaseListener {
    virtual void receive(const Event& event) = 0;
};

}    // namespace ecs
#endif    // ECS_ECS_EVENT_H_
