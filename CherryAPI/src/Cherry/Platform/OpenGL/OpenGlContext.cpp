#include "OpenGlContext.h"

#include <GL/glew.h>

namespace Cherry {

	void OpenGLContext::Init()
	{
		m_ctx = SDL_GL_CreateContext(m_WndHnd.get());

		printf("%s", glGetString(GL_VERSION));
	}

}
