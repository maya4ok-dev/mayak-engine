#pragma once

#include <SDL3/SDL.h>

#include "object.hpp"

#include <vector>
#include <string>
#include <unordered_set>

class DIM {
private:
    int width, height;
    std::vector<Object> objects;
public:
    static DIM *current;
    static std::vector<DIM> dims;

    static std::vector<DIM> GetDims() { return dims; }
    static void AddDim(DIM dim) { dims.emplace_back(std::move(dim)); }

    DIM(int width, int height) : width(width), height(height) {}
 
    int GetHeight() const { return height; }
    void SetHeight(int h) { height = h; }

    int GetWidth() const { return width; }
    void SetWidth(int w) { width = w; }

    static DIM& GetCurrDIM() { return *DIM::current; }
    static void SetCurrDIM(DIM *dim) { DIM::current = dim; }

    std::vector<Object>* GetObjects() { return &objects; }
    Object* AddObject(float x, float y, float height, float width, std::initializer_list<std::string> tagList, const char *path, AxisAlignedBoundingBox hitbox) { 
        std::unordered_set<std::string> tags = tagList;
        return &objects.emplace_back(x, y, height, width, std::move(tags), path, hitbox);
    }
};

//class World {
//    int width, height;
//    std::vector<Object> objects;
//public:
//    static World *current;
//    static std::vector<World> worlds;
//
//    static World *getCurrent();
//    static std::vector<World> *get
//    
//}
