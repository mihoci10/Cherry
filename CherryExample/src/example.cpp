#include <GL/glew.h>
#include <GLFW/glfw3.h>
int main() {
	int r = glfwInit(); 
	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	glfwMakeContextCurrent(window);
	GLenum res = glewInit();
	return 0;
}