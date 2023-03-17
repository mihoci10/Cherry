#pragma once

#include <SDL.h>
#include "imgui.h"

namespace Cherry::GUI{

    class ImGuiAPI {
    public:
        virtual ~ImGuiAPI() = default;

        virtual void Init() = 0;
        virtual void Deinit();
        virtual void NewFrame();
        virtual void DrawFrame() = 0;

        static std::unique_ptr<ImGuiAPI> Create(std::shared_ptr<SDL_Window> windowHandle);
    protected:
        ImGuiAPI();
    private:
        static bool s_Initialized;
    };
}