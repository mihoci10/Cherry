#pragma once

#include <Cherry/RendererAPI.h>

#include <SDL.h>
#include "imgui.h"
#include "imgui_internal.h"

namespace Cherry::GUI{

    class ImGuiAPI {
    public:
        virtual ~ImGuiAPI() = default;

        virtual void NewFrame();
        virtual void DrawFrame();
        virtual bool OnEvent(const SDL_Event* event);

        static std::unique_ptr<ImGuiAPI> Create(std::shared_ptr<RendererAPI> renderer);
    protected:
        ImGuiAPI(std::shared_ptr<RendererAPI> renderer);

        virtual void Initialize();
        virtual void Deinitialize();

        std::shared_ptr<RendererAPI> m_Renderer;
    };
}