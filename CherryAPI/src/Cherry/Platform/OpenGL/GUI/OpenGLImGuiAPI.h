#pragma once

#include <Cherry/GUI/ImGuiAPI.h>

namespace Cherry::GUI{

    class OpenGLImGuiAPI : public ImGuiAPI {

        virtual void Init() override;
        virtual void Deinit() override;
        virtual void NewFrame() override;
        virtual void DrawFrame() override;
    };

}