// File: DIM.h

#pragma once

#include <iostream>
#include <vector>
#include <string>

// в будущем использовать на объектах unique_ptr

class DIM;

extern DIM *currDIM;

struct Object{
    int r, g, b; // Object color
    float posX, posY, height, width; // Object parameters
    std::string type; // Object type parameter

    // Constructor and destructor
    Object(float posX, float posY, float height, float width, std::string type, int r, int g, int b)
    : posX(posX), posY(posY), height(height), width(width), type(type), r(r), g(g), b(b) { std::cout << "Created object " << this << std::endl; }

    ~Object() { std::cout << "Deleted object" << this << std::endl; }

    // Getters
    float GetPosX() const { std::cout << "called to get pos x" << std::endl; return posX; }
    float GetPosY() const { return posY; }
    float GetHeight() const { return height; }
    float GetWidth() const { return width; }
    int GetColorR() const { return r; }
    int GetColorG() const { return g; }
    int GetColorB() const { return b; }
    const std::string& GetType() const { return type; }

    // Setters
    void SetPosX(const float &x) { std::cout << "called to set pos x" << std::endl; posX = x; }
    void SetPosY(float y) { posY = y; }
    void SetHeight(float h) { height = h; }
    void SetWidth(float w) { width = w; }
    void SetColorR(int color) { r = color; }
    void SetColorG(int color) { g = color;}
    void SetColorB(int color) { b = color;}
    void SetType(const std::string& t) { type = t; }
};

class DIM {
private:
    int width, height; // Size of the dimension
    std::vector<Object> objects; // Vector to hold objects
public:
    static std::vector<DIM> dims;
    static std::vector<DIM> GetDims() { return dims; }
    static void AddDim(DIM dim) { dims.emplace_back(dim); }

    // Constructor and destructor
    DIM(int width, int height)
        : width(width), height(height) { AddDim(*this); }
    ~DIM() {}

    // Management methods
    Object* AddObject(float x, float y, float objHeight, float objWidth, const std::string& type, int r, int g, int b) { 
        std::cout << "called to add object" << std::endl;
        objects.emplace_back(x, y, objHeight, objWidth, type, r, g, b);
        return &objects.back();
    }
    
    // Getters
    int GetHeight() const { return height; }
    int GetWidth() const { return width; }
    const std::vector<Object>& GetObjects() const { return objects; }
    static DIM& GetCurrDIM() { return *currDIM; }

    // Setters
    void SetHeight(int h) { height = h; }
    void SetWidth(int w) { width = w; }
    static void SetCurrDIM(DIM *dim) { currDIM = dim; }
};
