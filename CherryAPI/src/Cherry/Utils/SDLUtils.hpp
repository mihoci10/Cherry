#pragma once

namespace Cherry {

	struct SDL_Deleter
	{
		void operator()(SDL_Window* p) const { SDL_DestroyWindow(p); }
		void operator()(SDL_GLContext p) const { SDL_GL_DeleteContext(p); }
	};

}