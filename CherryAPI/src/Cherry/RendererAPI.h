#pragma once

#include <glm/glm.hpp>
#include <SDL.h>

#include <Cherry/RendererSettings.hpp>
#include <Cherry/Buffer.h>

namespace Cherry{

    class RendererAPI {
    public:
        virtual ~RendererAPI() = default;

        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void DrawTriangles(VertexBuffer& vertexBuffer) = 0;
        virtual void Clear() = 0;

        SDL_Window& GetWindowHandle() const { return m_WindowHandle; };
        const RendererSettings& GetRendererSettings() const { return m_RendererSettings; };

        static std::unique_ptr<RendererAPI> Create(SDL_Window& windowHandle,
            RendererSettings rendererSettings);

    protected:
        RendererAPI(SDL_Window& windowHandle,
            RendererSettings rendererSettings);

        SDL_Window& m_WindowHandle;
        RendererSettings m_RendererSettings;
    };
}