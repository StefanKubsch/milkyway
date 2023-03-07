#include "./Shader/GeoShader.inl"

void LoadGeoShader()
{
	const GLuint Program{ glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &GeoSource) };
	glUseProgram(Program);

	glUniform1f(1, (GLfloat)(ScreenWidth));
	glUniform1f(2, (GLfloat)(ScreenHeight));
}

void RenderGeoShader()
{
	waveOutGetPosition(WaveOut, &MMTime, sizeof(MMTIME));
	glUniform1f(0, (float)(MMTime.u.sample));

	// Get BassDrum note (int = 46) on Instrument Channel 3 (Counting starts with 0!)
	constexpr int BassDrumChannel{ 2 };
	glUniform1f(3, (float)((&_4klang_note_buffer)[((MMTime.u.sample >> 8) << 5) + (BassDrumChannel << 1)]));
}