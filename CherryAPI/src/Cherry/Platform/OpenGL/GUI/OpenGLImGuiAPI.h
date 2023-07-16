#pragma once

#include <Cherry/GUI/ImGuiAPI.h>

namespace Cherry::GUI{

    class OpenGLImGuiAPI : public ImGuiAPI {

    public:
        OpenGLImGuiAPI(std::shared_ptr<RendererAPI> renderer);
        ~OpenGLImGuiAPI();

        virtual void NewFrame() override;
        virtual void DrawFrame() override;

    private:
        virtual void Initialize() override;
        virtual void Deinitialize() override;
    };

}