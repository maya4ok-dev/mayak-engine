// File: Renderer.cpp

#include "Renderer.hpp"
#include "DIM.hpp"
#include "Scripting.hpp"
#include "Logger.hpp"
#include "mayak/logger/core/logger.hpp"

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
        if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
            mlogger.setLevel(info);
            mlogger << "failed to initialize sdl: " << SDL_GetError() << logger::core::flush;
            return false;
        }

        // Create SDL window
        window = SDL_CreateWindow(windowName, DIM::GetCurrDIM().GetWidth(), DIM::GetCurrDIM().GetHeight(), 0);
        if (window == nullptr) {
            mlogger.setLevel(info);
            mlogger << "failed to create window: " << SDL_GetError() << logger::core::flush;
            return false;
        }

        // Create SDL renderer
        renderer = SDL_CreateRenderer(window, nullptr); // nullptr is the default renderer
        if (renderer == nullptr) { // If the render wasn't created
            mlogger.setLevel(info);
            mlogger << "failed to create renderer: " << SDL_GetError() << logger::core::flush;
            return false;
        }

        // Enable VSync
        if(!SDL_SetRenderVSync(renderer, VSync)) {
            mlogger.setLevel(info);
            mlogger << "failed to set VSync: " << SDL_GetError() << logger::core::flush;
        }

        mlogger.setLevel(info);
        mlogger << "set vsync to " << (VSync ? "on" : "off") << logger::core::flush;

        for (const auto& obj : DIM::GetCurrDIM().GetObjects()) {
            const std::string& path = obj->GetPath();
            if (textureCache.find(path) == textureCache.end()) {
                int width, height, channels;
                unsigned char* pixels = stbi_load(obj->GetPath().c_str(), &width, &height, &channels, 4);
                if (!pixels) {
                    mlogger.setLevel(info);
                    mlogger << "failed to load textures: " << stbi_failure_reason() << logger::core::flush;
                    return false;
                }
                SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, width, height);
                SDL_UpdateTexture(texture, nullptr, pixels, width * 4);
                stbi_image_free(pixels);
                textureCache[path] = {texture, width, height};
            }
        }

        mlogger.setLevel(info);
        mlogger << "initialized SDL successfully" << logger::core::flush;

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

