#include "ImGuiAPI.h"

#include <Cherry/Utils/Log.hpp>
#include <Cherry/RendererAPI.h>
#include <Cherry/Platform/OpenGL/GUI/OpenGLImGuiAPI.h>

#include "backends/imgui_impl_sdl3.h"

namespace Cherry::GUI {

    bool ImGuiAPI::s_Initialized = false;

    ImGuiAPI::ImGuiAPI()
    {
    }

    void ImGuiAPI::Init()
    {
        ImGui::CreateContext();
    }

    void ImGuiAPI::Deinit()
    {
        ImGui_ImplSDL3_Shutdown();
        s_Initialized = false;
    }

    void ImGuiAPI::NewFrame()
    {
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiAPI::DrawFrame()
    {
        ImGui::Render();
    }

    bool ImGuiAPI::OnEvent(const SDL_Event* event)
    {
        return ImGui_ImplSDL3_ProcessEvent(event);
    }

    std::unique_ptr<ImGuiAPI> ImGuiAPI::Create()
    {
        if (s_Initialized)
            CHERRY_THROW("Cannot initialize ImGuiAPI twice!");

        std::unique_ptr<ImGuiAPI> result = nullptr;

        switch (Cherry::RendererAPI::GetSettings()->platform)
        {
        case Cherry::RendererPlatform::None:
            CHERRY_THROW("Headless mode is not supported by ImGui API!");
            break;
        case Cherry::RendererPlatform::OpenGL:
            result = std::make_unique<OpenGLImGuiAPI>();
            break;
        case Cherry::RendererPlatform::Vulkan:
            CHERRY_THROW("Vulcan platform is not supported by ImGui API!");
            break;
        }

        s_Initialized = true;

        return result;
    }
}