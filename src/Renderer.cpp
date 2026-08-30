// File: Renderer.cpp

#include "Renderer.hpp"
#include "DIM.hpp"
#include "Scripting.hpp"

#include <map>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace{
    bool VSync = false;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    struct CachedTexture {
        SDL_Texture* texture;
        int width;
        int height;
    };

    std::map<std::string, CachedTexture> textureCache;
}

namespace mayak::gfx {
    bool init(const char* windowName) {
        // Initialize SDL
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
//            MAYAK_LOG_FATAL("Failed to initialize SDL:" + std::string(SDL_GetError()));
            return false;
        }

        // Create SDL window
        window = SDL_CreateWindow(windowName, DIM::GetCurrDIM().GetWidth(), DIM::GetCurrDIM().GetHeight(), 0);
        if (window == nullptr) {
//            MAYAK_LOG_FATAL("Failed to create SDL window:" + std::string(SDL_GetError()));
            return false;
        }

        // Create SDL renderer
        renderer = SDL_CreateRenderer(window, nullptr); // nullptr is the default renderer
        if (renderer == nullptr) { // If the render wasn't created
//            MAYAK_LOG_FATAL("Failed to create SDL renderer:" + std::string(SDL_GetError()));
            return false;
        }

        // Enable VSync
        if(!SDL_SetRenderVSync(renderer, VSync)) 
//            MAYAK_LOG_WARN("Failed to set VSync:" + std::string(SDL_GetError()));
//        MAYAK_LOG_DEBUG("VSync is " + std::to_string(VSync));

//        MAYAK_LOG_INFO("Loading textures...");
        for (const auto& obj : DIM::GetCurrDIM().GetObjects()) {
            const std::string& path = obj->GetPath();
            if (textureCache.find(path) == textureCache.end()) {
                int width, height, channels;
                unsigned char* pixels = stbi_load(obj->GetPath().c_str(), &width, &height, &channels, 4);
                if (!pixels) {
//                    MAYAK_LOG_FATAL("Failed to load texture:" + std::string(stbi_failure_reason()));
                    return false;
                }
                SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, width, height);
                SDL_UpdateTexture(texture, nullptr, pixels, width * 4);
                stbi_image_free(pixels);
                textureCache[path] = {texture, width, height};
            }
        }
//        MAYAK_LOG_INFO("Textures loaded");

//        MAYAK_LOG_INFO("Renderer initialized successfully!");
        return true;
    }

    void render() {
        if (!isInitialized()) {
//            MAYAK_LOG_WARN("Renderer is not initialized");
            return;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Render every object
        for (const auto& obj : DIM::GetCurrDIM().GetObjects()) {
            SDL_Texture* texture = textureCache[obj->GetPath()].texture;
            if (!texture) {
//                MAYAK_LOG_ERROR("Texture not found:" + obj->GetPath());
                return;
            }

            SDL_FRect rect = {obj->GetPosX(), obj->GetPosY(), obj->GetWidth(), obj->GetHeight()};

            if (!SDL_RenderTexture(renderer, texture, nullptr, &rect)) {
//                MAYAK_LOG_FATAL("Failed to render texture:" + std::string(SDL_GetError()));
                return;
            }
        }
        
        SDL_RenderPresent(renderer);
    }

    void cleanup() {
//        MAYAK_LOG_INFO("Cleaning up...");
        
        for (auto& pair : textureCache) {
            SDL_DestroyTexture(pair.second.texture);
        }
        textureCache.clear();
        
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);

        // Clear pointers
        renderer = nullptr;
        window = nullptr;
        
//        MAYAK_LOG_INFO("Cleanup complete!");
    }

    bool isInitialized() noexcept {
        return window != nullptr && renderer != nullptr;
    }

    bool getVSync() noexcept {
        return VSync;
    }
    
    void setVSync(bool value) {
        VSync = value;
        SDL_SetRenderVSync(renderer, VSync);
//        MAYAK_LOG_DEBUG("VSync is " + std::to_string(VSync));
    }
}

