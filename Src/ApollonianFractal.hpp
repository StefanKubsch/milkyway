// Include our GLSL code here
#include "./Shader/ApollonianFractal.inl"

void LoadFractalShader()
{
	const GLuint Program{ glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &ApollonianFractalSource) };
	glUseProgram(Program);

	glUniform1f(1, static_cast<GLfloat>(ScreenWidth));
	glUniform1f(2, static_cast<GLfloat>(ScreenHeight));
}

void RenderFractalShader()
{
	waveOutGetPosition(WaveOut, &MMTime, sizeof(MMTIME));

	glUniform1f(0, static_cast<GLfloat>(MMTime.u.sample));

	// Get notes from 4klang stream
	// Channels starts with 0 and end with 15; so channel 0 equals MIDI channel 1!
	// General call: (&_4klang_note_buffer)[((MMTime.u.sample >> 8) << 5) + (ChannelNumber << 1)])
	// Or without bitshifting: (&_4klang_note_buffer)[((MMTime.u.sample / 256) * 32) + (ChannelNumber * 2)])

	constexpr int BassDrumChannel{ 2 * 2 };
	constexpr int SnareDrumChannel{ 3 * 2 };

	glUniform1f(3, static_cast<GLfloat>((&_4klang_note_buffer)[((MMTime.u.sample >> 8) << 5) + BassDrumChannel]));
	glUniform1f(4, static_cast<GLfloat>((&_4klang_note_buffer)[((MMTime.u.sample >> 8) << 5) + SnareDrumChannel]));

	// Bring everything to screen
	glRects(-1, -1, 1, 1);
	SwapBuffers(WindowHandle);
}