#pragma once

#include <glm/glm.hpp>
#include <SDL.h>

#include <Cherry/RendererSettings.hpp>
#include <Cherry/BufferBatch.h>

namespace Cherry{

    class RendererAPI {
    public:
        virtual ~RendererAPI() = default;

        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const = 0;
        virtual void SetClearColor(const glm::vec4& color) const = 0;
        virtual void Draw(VertexBuffer& vertexBuffer) const = 0;
        virtual void Draw(BufferBatch& bufferBatch) const = 0;
        virtual void Clear() const = 0;

        std::shared_ptr<SDL_Window> GetWindowHandle() const { return m_WindowHandle; };
        const RendererSettings& GetRendererSettings() const { return m_RendererSettings; };

        static std::unique_ptr<RendererAPI> Create(std::shared_ptr<SDL_Window> windowHandle,
            RendererSettings rendererSettings);

    protected:
        RendererAPI(std::shared_ptr<SDL_Window> windowHandle,
            RendererSettings rendererSettings);

        std::shared_ptr<SDL_Window> m_WindowHandle;
        RendererSettings m_RendererSettings;
    };
}