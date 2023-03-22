#pragma once

#include <SDL.h>
#include "imgui.h"

namespace Cherry::GUI{

    class ImGuiAPI {
    public:
        virtual ~ImGuiAPI() = default;

        virtual void Init();
        virtual void Deinit();
        virtual void NewFrame();
        virtual void DrawFrame();

        static std::unique_ptr<ImGuiAPI> Create();
    protected:
        ImGuiAPI();
    private:
        static bool s_Initialized;
    };
}