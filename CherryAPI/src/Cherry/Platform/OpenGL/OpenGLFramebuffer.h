#pragma once

#include <Cherry/Framebuffer.h>

namespace Cherry{

    class OpenGLFramebuffer: public Framebuffer {
    public:
        OpenGLFramebuffer(const FramebufferSpecification& framebufferSpecification);
        virtual ~OpenGLFramebuffer();

        virtual void Bind() override;
        virtual void Unbind() override;

        virtual void Resize(uint32_t width, uint32_t height) override;
        virtual uint32_t GetColorAttachmentID(uint32_t index = 0) override;

    private:
        void Init();
        void Deinit();

        uint32_t GetTextureTarget();
        void CreateTexture(uint32_t* textureID);
        void BindTexture(uint32_t textureID);

        void AttachColorTexture(uint32_t textureID, uint32_t internalFormat, uint32_t format, int index);
        void AttachDepthTexture(uint32_t textureID, uint32_t format, uint32_t attachmentType);

        uint32_t m_FramebufferID = 0;
        FramebufferSpecification m_FramebufferSpecification;
        std::vector<uint32_t> m_ColorAttachments = {};
        uint32_t m_DepthAttachment = 0;

        static constexpr uint32_t s_MaxFrameSize = 8192;
    };

}