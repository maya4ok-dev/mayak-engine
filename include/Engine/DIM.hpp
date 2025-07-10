// File: DIM.h

#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <SDL3/SDL.h>
#include <memory>
#include <unordered_set>

#include "glm/vec2.hpp"

class DIM;
extern DIM *currDIM;

using Entity = uint32_t;
const Entity INVALID_ENTITY = 0;

class EntityManager {
    Entity nextID = 1;
    std::unordered_set<Entity> entities;

    public:
    Entity Create() {
        Entity id = nextID++;
        entities.insert(id);
        return id;
    }

    void destroy(Entity entity) {
        entities.erase(entity);
        // TODO: Destroy all components of the entity
    }

    bool isValid(Entity entity) {
        return entities.contains(entity);
    }

    const std::unordered_set<Entity>& getAll() const {
        return entities;
    }
};

// struct AxisAlignedBoundingBox {
//     glm::vec2 lowerLeft;
//     glm::vec2 upperRight;

//     AxisAlignedBoundingBox(const glm::vec2& ll, const glm::vec2& ur)
//         : lowerLeft(ll), upperRight(ur) {}

//     AxisAlignedBoundingBox(const glm::vec2& position, float width, float height)
//         : lowerLeft(position), upperRight(glm::vec2(position.x + width, position.y + height)) {}

//     bool Intersects(const AxisAlignedBoundingBox& other) const {
//         return !(upperRight.x < other.lowerLeft.x ||
//                  lowerLeft.x > other.upperRight.x ||
//                  upperRight.y < other.lowerLeft.y ||
//                  lowerLeft.y > other.upperRight.y);
//     }

//     // Getters
//     float GetLowerLeftX() const { return lowerLeft.x; }
//     float GetLowerLeftY() const { return lowerLeft.y; }
//     float GetUpperRightX() const { return upperRight.x; }
//     float GetUpperRightY() const { return upperRight.y; }
// };

// struct PositionComponent { glm::vec2 position; };
// struct SizeComponent { float width, height; };


// struct Object{
//     float posX, posY, height, width;
//     const char* path;
//     std::unordered_set<std::string> tags;
//     bool isVisible;
//     AxisAlignedBoundingBox hitbox;

//     Object(float posX, float posY, float height, float width, std::unordered_set<std::string> tags, const char* path, AxisAlignedBoundingBox hitbox)
//     : posX(posX), posY(posY), height(height), width(width), tags(tags), path(path), hitbox(hitbox) {}

//     ~Object() {}

//     // Getters
//     float GetPosX() const { return posX; }
//     float GetPosY() const { return posY; }
//     float GetHeight() const { return height; }
//     float GetWidth() const { return width; }
//     const std::string GetPath() const { return path; }
//     bool HasTag(const std::string& tag) const { return tags.find(tag) != tags.end(); }
//     bool IsVisible() const { return isVisible; }

//     // Setters
//     void SetPosX(const float &x) { posX = x; }
//     void SetPosY(float y) { posY = y; }
//     void SetHeight(float h) { height = h; }
//     void SetWidth(float w) { width = w; }
//     void SetPath(const char * p) { path = p; }
//     void AddTag(const std::string& tag) { tags.insert(tag); }
//     void RemoveTag(const std::string& tag) { tags.erase(tag); }
//     void SetVisible(bool state) { isVisible = state; }
// };

// class DIM {
// private:
//     int width, height; // dim size
//     std::vector<std::shared_ptr<Object>> objects; // object vector
// public:
//     static std::vector<DIM> dims;
//     static std::vector<DIM> GetDims() { return dims; }
//     static void AddDim(DIM dim) { dims.emplace_back(dim); }

//     DIM(int width, int height)
//         : width(width), height(height) { AddDim(*this); }
//     ~DIM() {}
    
//     int GetHeight() const { return height; }
//     int GetWidth() const { return width; }
//     std::vector<std::shared_ptr<Object>> GetObjects() {
//         std::vector<std::shared_ptr<Object>> result;
//         for (auto& obj : objects) {
//             result.push_back(obj);
//         }
//         return result;
//     }
//     static DIM& GetCurrDIM() { return *currDIM; }

//     void SetHeight(int h) { height = h; }
//     void SetWidth(int w) { width = w; }
//     static void SetCurrDIM(DIM *dim) { currDIM = dim; }
//     std::shared_ptr<Object> AddObject(float x, float y, float objHeight, float objWidth, std::vector<std::string> tagsVec, const char * path, AxisAlignedBoundingBox hitbox) { 
//         std::unordered_set<std::string> tags(tagsVec.begin(), tagsVec.end());
//         auto obj = std::make_shared<Object>(x, y, objHeight, objWidth, std::move(tags), path, hitbox);
//         objects.emplace_back(obj);
//         return obj;
//     }
// };
