#pragma once

#include <Cherry/RendererSettings.hpp>

namespace Cherry{

    enum class FramebufferTextureFormat {
        Color, Depth
    };

    struct FramebufferSpecification {
        uint32_t Width = 0, Height = 0;
        uint32_t Samples = 1;
        std::vector<FramebufferTextureFormat> Attachments;
    };

    class Framebuffer {
    public:
        virtual ~Framebuffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;
        virtual uint32_t GetColorAttachmentID(uint32_t index = 0) = 0;

        static std::unique_ptr<Framebuffer> Create(const RendererSettings& rendererSettings, 
            const FramebufferSpecification& framebufferSpecification);

    protected:
        Framebuffer();
    };

}