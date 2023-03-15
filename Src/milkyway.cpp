// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <Windows.h>

// Screensize
#define ScreenWidth		1280
#define ScreenHeight	720

// Include framework specific headers
#include "Memory.hpp"
#include "OpenGL_Loader.hpp"
#include "OpenGL_Screen.hpp"
#include "4klang_Synth.hpp"

// Include content/demo/intro headers here
#include "GeoShader.hpp"

// Create a custom "naked" entry point, so we don´t include CRT (C Runtime).
// Doing this, we create a "bare metal" binary file, which is not linked to any standard libraries. Neither static, nor dynamic!
__declspec(naked) void winmain()
{
	// Prologue
	__asm enter 0x10, 0;
	__asm pushad;

	// Create an extra scope so we can use local vars, since "naked" functions don´t allow them
	{
		InitScreen();
		InitOpenGL();
		ClearScreen();
		LoadGeoShader();
		InitSynth();

		// Main loop
		do
		{
			// Do some minimal Windows message handling, otherwise Windows will kick your application after some seconds
			PeekMessage(nullptr, nullptr, 0, 0, PM_REMOVE);

			// Here starts our demo/intro code
			RenderGeoShader();
			// Here ends our demo/intro code
		} while ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) == 0 && MMTime.u.sample < MAX_SAMPLES);
	}

	DestroyScreen();
	ExitProcess(0);
}