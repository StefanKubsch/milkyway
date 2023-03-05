#include <Windows.h>

HDC WindowHandle{};
HWND MainWindow{};

void InitScreen()
{
	// Enter fullscreen mode

	DEVMODE ScreenSettings{ { 0 }, 0, 0, sizeof(DEVMODE), 0, DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL, { 0 }, 0, 0, 0, 0, 0, { 0 }, 0, 32, ScreenWidth, ScreenHeight, { 0 }, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	ChangeDisplaySettings(&ScreenSettings, CDS_FULLSCREEN);
	ShowCursor(0);

	// Create OpenGL context
	// https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL)

	constexpr PIXELFORMATDESCRIPTOR PFD{ sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 8, 0, PFD_MAIN_PLANE, 0, 0, 0, 0 };

	MainWindow = CreateWindow((LPCSTR)0xC018, 0, WS_POPUP | WS_VISIBLE | WS_MAXIMIZE, 0, 0, 0, 0, 0, 0, 0, 0);
	WindowHandle = GetDC(MainWindow);

	SetPixelFormat(WindowHandle, ChoosePixelFormat(WindowHandle, &PFD), &PFD);
	wglMakeCurrent(WindowHandle, wglCreateContext(WindowHandle));
}

void DeleteOpenGLContext()
{
	const HGLRC OpenGLContext{ wglGetCurrentContext() };
	wglMakeCurrent(nullptr, nullptr);
	ReleaseDC(MainWindow, WindowHandle);
	wglDeleteContext(OpenGLContext);
}

void ClearScreen()
{
	glColor4f(0.0F, 0.0F, 0.0F, 0.0F);
	glClear(GL_COLOR_BUFFER_BIT);
	SwapBuffers(WindowHandle);
}