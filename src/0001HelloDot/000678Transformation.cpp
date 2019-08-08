//////////////////////////////////////////////////////////////////////////////
//
//  Triangles.cpp
//
//////////////////////////////////////////////////////////////////////////////

#include "vgl.h"
#include "LoadShaders.h"
#include <math.h>
#include "vmath.h"

enum Buffer_IDs { ArrayBuffer, NumBuffers };
GLuint  Buffers[NumBuffers];

GLuint gWorldLocation;
//----------------------------------------------------------------------------
//
// init
//


void
init(void)
{
	float triangleSize = 0.5f;
	GLfloat Vertices[9] = { -triangleSize, -triangleSize, triangleSize, -triangleSize, 0.0f, triangleSize };

	glGenBuffers(1, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);


	ShaderInfo  shaders[] =
	{
		{ GL_VERTEX_SHADER, "../bin/media/shaders/stepbystep/stepbystep06.vs" },
		{ GL_FRAGMENT_SHADER, "../bin/media/shaders/stepbystep/stepbystep06.fs" },
		{ GL_NONE, NULL }
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	gWorldLocation = glGetUniformLocation(program, "gWorld");
}

//----------------------------------------------------------------------------
//
// display
//

void
display(void)
{
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	glClearBufferfv(GL_COLOR, 0, black);



	static float Scale = 0.0f;

	Scale += 0.01f;

	vmath::mat4 World = vmath::translate((float)(sin(Scale)), 0.0f, 0.0f);
	//vmath::mat4 World = vmath::rotate(Scale*100.0f, 0.0f, 1.0f, 0.0f);
	//vmath::mat4 World = vmath::scale((float)(sin(Scale)));

	glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, World.transpose());

	glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
}

//----------------------------------------------------------------------------
//
// main
//

#ifdef _WIN32
int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
#else
int
main(int argc, char** argv)
#endif
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(800, 600, "Triangles", NULL, NULL);

	glfwMakeContextCurrent(window);
	gl3wInit();

	init();

	while (!glfwWindowShouldClose(window))
	{
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
}
