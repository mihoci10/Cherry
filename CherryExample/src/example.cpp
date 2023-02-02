#include <GL/glew.h>
#include <SDL3/SDL.h>
int main() {
	int r = SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* mainwindow = SDL_CreateWindow("CherryExample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		512, 512, SDL_WINDOW_OPENGL);
	SDL_GLContext maincontext = SDL_GL_CreateContext(mainwindow);
	GLenum res = glewInit();
	return 0;
}