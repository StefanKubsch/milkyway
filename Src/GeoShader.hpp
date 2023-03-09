// Include our GLSL code here
#include "./Shader/GeoShader.inl"

void LoadGeoShader()
{
	const GLuint Program{ glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &GeoSource) };
	glUseProgram(Program);

	glUniform1f(1, static_cast<GLfloat>(ScreenWidth));
	glUniform1f(2, static_cast<GLfloat>(ScreenHeight));
}

void RenderGeoShader()
{
	waveOutGetPosition(WaveOut, &MMTime, sizeof(MMTIME));

	glUniform1f(0, static_cast<GLfloat>(MMTime.u.sample));

	// Get BassDrum note (here: int = 46) on instrument Channel 3 (counting starts with 0!)
	//
	// general call: (&_4klang_note_buffer)[((MMTime.u.sample >> 8) << 5) + (ChannelNumber << 1)])
	// or without bit-shifting: (&_4klang_note_buffer)[((MMTime.u.sample / 256) * 32) + (ChannelNumber * 2)])

	constexpr int BassDrumChannel{ 2 };
	glUniform1f(3, static_cast<GLfloat>((&_4klang_note_buffer)[((MMTime.u.sample >> 8) << 5) + (BassDrumChannel << 1)]));
}