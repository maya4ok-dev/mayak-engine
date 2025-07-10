#pragma once
#include <string>
#include <unordered_set>

namespace mayak::ecs {

    struct Tags {
        std::unordered_set<std::string> tags;

        Tags() = default;

        explicit Tags(std::initializer_list<const char*> init) {
            for (auto& s : init) tags.insert(s);
        }

        void add(const std::string& tag) {
            tags.insert(tag);
        }

        void add(const char* tag) {
            tags.insert(tag);
        }

        bool has(const std::string& tag) const {
            return tags.contains(tag);
        }

        bool has(const char* tag) const {
            return tags.contains(tag);
        }

        void remove(const std::string& tag) {
            tags.erase(tag);
        }

        void remove(const char* tag) {
            tags.erase(tag);
        }
    };
}