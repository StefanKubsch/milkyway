// For more information about how to load OpenGL functions, have a look here:
// https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions#Windows_2

#include <GL/gl.h>

// Definitions can be found here:
// https://www.khronos.org/registry/OpenGL/api/GL/glext.h
//
// Please take care: Only things used are defined here - of course, there are much more possible definitions!

#define GL_FRAGMENT_SHADER	0x8B30

// And all those nice function definitions can be found here:
// https://www.khronos.org/registry/OpenGL-Refpages/gl4/
// and also here - please take care: Only functions used are defined here - of course, there are much more!

#define OGL \
	OG(GLuint,	glCreateShaderProgramv,		GLenum type, GLsizei count, const char** strings) \
	OG(void,	glUniform1f,				GLint location, GLfloat v0) \
	OG(void,	glUseProgram,				GLuint program)
#define OG(Return, Name, ...) typedef Return WINAPI Name##proc(__VA_ARGS__); extern Name##proc* Name;
OGL
#undef OG

#define OG(Return, Name, ...) Name##proc * Name;
OGL
#undef OG

void InitOpenGL()
{
	const HMODULE OGL32{ LoadLibrary("opengl32.dll") };
	using wglGetProcAddressproc = PROC WINAPI(LPCSTR);
	wglGetProcAddressproc* wglGetProcAddress{ reinterpret_cast<wglGetProcAddressproc*>(GetProcAddress(OGL32, "wglGetProcAddress")) };

	#define OG(Return, Name, ...) Name = reinterpret_cast<Name##proc *>(wglGetProcAddress(#Name));
		OGL
	#undef OG
}