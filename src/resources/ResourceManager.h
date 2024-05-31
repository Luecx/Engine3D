#ifndef ENGINE3D_RESOURCEMANAGER_H
#define ENGINE3D_RESOURCEMANAGER_H

#include "Resource.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct ResourceGroup;

using ResourceGroupPtr = std::shared_ptr<ResourceGroup>;

struct ResourceGroup : std::enable_shared_from_this<ResourceGroup> {
    std::vector<std::shared_ptr<Resource>> resources {};
    std::unordered_set<ResourceGroupPtr>   parents {};
    std::unordered_set<ResourceGroupPtr>   children {};

    // add a resource to the group using a templated version which takes the arguments for the resource constructor
    template <typename T, typename... Args>
    std::shared_ptr<T> add(Args&&... args) {
        auto resource = std::make_shared<T>(std::forward<Args>(args)...);
        resources.push_back(resource);
        return resource;
    }

    // remove a resource
    void remove(const std::shared_ptr<Resource>& resource) {
        resources.erase(std::remove(resources.begin(), resources.end(), resource), resources.end());
    }

    void add_child(const ResourceGroupPtr& child) {
        children.insert(child);
        child->parents.insert(shared_from_this());
    }

    void remove_child(const ResourceGroupPtr& child) {
        children.erase(child);
        child->parents.erase(shared_from_this());
    }

    void load_resources() {
        for (const auto& resource : resources) {
            resource->load();
        }
        // Recursively load resources for children
        for (const auto& child : children) {
            child->load_resources();
        }
    }

    void unload_resources(bool recursive = true) {
        for (const auto& resource : resources) {
            resource->unload();
        }

        if (!recursive) {
            return;
        }

        // Recursively unload resources for children
        for (const auto& child : children) {
            child->unload_resources();
        }
    }
};

class ResourceManager {
    public:
    ResourceGroupPtr add_sub_group(const std::vector<ResourceGroupPtr>& bases) {
        auto newGroup = std::make_shared<ResourceGroup>();
        for (const auto& base : bases) {
            base->add_child(newGroup);
        }
        groups.push_back(newGroup);
        return newGroup;
    }

    void remove_group(const ResourceGroupPtr& group) {
        for (const auto& parent : group->parents) {
            parent->remove_child(group);
        }
        for (const auto& child : group->children) {
            child->parents.erase(group);
            if (child->parents.empty()) {
                remove_group(child);    // Recursively remove children without other parents
            }
        }
        // remove the group out of the groups using erase if
        groups.erase(std::remove(groups.begin(), groups.end(), group), groups.end());
    }

    void remove_all() {
        for (const auto& group : groups) {
            group->unload_resources(false);
        }
        groups.clear();
    }

    private:
    std::vector<ResourceGroupPtr> groups {};
};

#endif    // ENGINE3D_RESOURCEMANAGER_H
