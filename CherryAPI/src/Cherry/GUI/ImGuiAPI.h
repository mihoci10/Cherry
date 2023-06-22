#pragma once

#include <SDL.h>
#include "imgui.h"
#include "imgui_internal.h"

namespace Cherry::GUI{

    class ImGuiAPI {
    public:
        virtual ~ImGuiAPI() = default;

        virtual void Init();
        virtual void Deinit();
        virtual void NewFrame();
        virtual void DrawFrame();
        virtual bool OnEvent(const SDL_Event* event);

        static std::unique_ptr<ImGuiAPI> Create();
    protected:
        ImGuiAPI();
    private:
        static bool s_Initialized;
    };
}