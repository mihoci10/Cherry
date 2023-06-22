#include "OpenGLFramebuffer.h"

#include <Cherry/Utils/Log.hpp>
#include <GL/glew.h>

namespace Cherry{

    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& framebufferSpecification)
        : m_FramebufferSpecification(framebufferSpecification)
    {  
        Init();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        Deinit();
    }

    void OpenGLFramebuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
    }

    void OpenGLFramebuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
    {
        if(width == 0 || width > s_MaxFrameSize)
            CHERRY_THROW("Cannot set framebuffer width to %d", width);
        if (height == 0 || height > s_MaxFrameSize)
            CHERRY_THROW("Cannot set framebuffer height to %d", height);

        m_FramebufferSpecification.Width = width;
        m_FramebufferSpecification.Height = height;

        Deinit();
        Init();
    }

    uint32_t OpenGLFramebuffer::GetColorAttachmentID(uint32_t index)
    {
        return m_ColorAttachments[index];
    }

    void OpenGLFramebuffer::Init()
    {
        glCreateFramebuffers(1, &m_FramebufferID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);

        for (auto& attachment : m_FramebufferSpecification.Attachments)
        {
            switch (attachment)
            {
            case FramebufferTextureFormat::Color:
                m_ColorAttachments.push_back(0);
                CreateTexture(m_ColorAttachments.data() + m_ColorAttachments.size() - 1);
                BindTexture(m_ColorAttachments.back());
                AttachColorTexture(m_ColorAttachments.back(), GL_RGBA8, GL_RGBA, m_ColorAttachments.size() - 1);
                break;
            case FramebufferTextureFormat::Depth:
                CreateTexture(&m_DepthAttachment);
                BindTexture(m_DepthAttachment);
                AttachDepthTexture(m_DepthAttachment, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
                break;
            }
        }

        if (m_ColorAttachments.size() > 4)
            CHERRY_THROW("OpenGL framebuffer does not support more than 4 color attachments!");

        if (m_ColorAttachments.size() > 0) {
            static constexpr GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
            glDrawBuffers(m_ColorAttachments.size(), buffers);
        }
        else {
            glDrawBuffer(GL_NONE);
        }

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            CHERRY_THROW("Framebuffer initialization error!");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::Deinit()
    {
        glDeleteFramebuffers(1, &m_FramebufferID);
        glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
        glDeleteTextures(1, &m_DepthAttachment);

        m_ColorAttachments.clear();
        m_DepthAttachment = 0;
    }

    uint32_t OpenGLFramebuffer::GetTextureTarget()
    {
        return m_FramebufferSpecification.Samples > 1 ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
    }

    void OpenGLFramebuffer::CreateTexture(uint32_t* textureID)
    {
        glCreateTextures(GetTextureTarget(), 1, textureID);
    }

    void OpenGLFramebuffer::BindTexture(uint32_t textureID)
    {
        glBindTexture(GetTextureTarget(), textureID);
    }

    void OpenGLFramebuffer::AttachColorTexture(uint32_t textureID, uint32_t internalFormat, uint32_t format, int index)
    {
        if (m_FramebufferSpecification.Samples > 1)
        {
            glTexImage2DMultisample(
                GL_TEXTURE_2D_MULTISAMPLE, 
                m_FramebufferSpecification.Samples, 
                internalFormat, 
                m_FramebufferSpecification.Width, m_FramebufferSpecification.Height, 
                GL_FALSE
            );
        }
        else
        {
            glTexImage2D(
                GL_TEXTURE_2D, 
                0, 
                internalFormat, 
                m_FramebufferSpecification.Width, m_FramebufferSpecification.Height, 
                0, 
                format,
                GL_UNSIGNED_BYTE, 
                nullptr
            );

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GetTextureTarget(), textureID, 0);
    }

    void OpenGLFramebuffer::AttachDepthTexture(uint32_t textureID, uint32_t format, uint32_t attachmentType)
    {
        if (m_FramebufferSpecification.Samples > 1)
        {
            glTexImage2DMultisample(
                GL_TEXTURE_2D_MULTISAMPLE,
                m_FramebufferSpecification.Samples, 
                format,
                m_FramebufferSpecification.Width, m_FramebufferSpecification.Height,
                GL_FALSE
            );
        }
        else
        {
            glTexStorage2D(GL_TEXTURE_2D, 1, format, m_FramebufferSpecification.Width, m_FramebufferSpecification.Height);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }

        glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GetTextureTarget(), textureID, 0);
    }

}