#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <Cherry/RendererSettings.hpp>

namespace Cherry{

    class RendererAPI {
    public:
        RendererAPI(std::shared_ptr<RendererSettings> rendererSettings) : m_Settings(rendererSettings) {};
        virtual ~RendererAPI() = default;

        virtual void Init() = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        auto GetSettings() { return m_Settings; }
        static std::unique_ptr<RendererAPI> Create(std::shared_ptr<RendererSettings> rendererSettings);

    protected:
        std::shared_ptr<RendererSettings> m_Settings = nullptr;
    };
}