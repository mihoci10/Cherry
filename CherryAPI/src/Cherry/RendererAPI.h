#pragma once

#include <glm/glm.hpp>
#include <SDL.h>

#include <Cherry/RendererSettings.hpp>

namespace Cherry{

    class RendererAPI {
    public:
        virtual ~RendererAPI() = default;

        virtual void Init() = 0;
        virtual void Deinit();
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        static const auto GetWindowHnd() { return s_WndHnd; }
        static const auto GetSettings() { return s_Settings; }
        static std::unique_ptr<RendererAPI> Create(std::shared_ptr<SDL_Window> windowHandle,
            std::shared_ptr<RendererSettings> rendererSettings);

    protected:
        RendererAPI();
    private:
        static bool s_Initialized;
        static std::shared_ptr<SDL_Window> s_WndHnd;
        static std::shared_ptr<RendererSettings> s_Settings;
    };
}