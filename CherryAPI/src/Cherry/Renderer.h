#pragma once

#include <Cherry/RendererAPI.h>

namespace Cherry{

    class Renderer {
    public:

        static void Create(std::shared_ptr<SDL_Window> windowHandle,
            std::shared_ptr<RendererSettings> rendererSettings);

        static void Init() {
            s_RendererAPI->Init();
        }
        static void Deinit() {
            s_RendererAPI->Deinit();
        }
        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
            s_RendererAPI->SetViewport(x, y, width, height);
        }
        static void SetClearColor(const glm::vec4& color) {
            s_RendererAPI->SetClearColor(color);
        }
        static void DrawTriangles(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
            s_RendererAPI->DrawTriangles(vertexBuffer);
        }
        static void Clear() {
            s_RendererAPI->Clear();
        }

    private:
        static std::unique_ptr<RendererAPI> s_RendererAPI;
    };

}