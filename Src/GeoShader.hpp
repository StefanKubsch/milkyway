#include "./Shader/GeoShader.inl"

GLuint GeoShaderProgram{};

void LoadGeoShader()
{
	GeoShaderProgram = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &GeoSource);
	glUseProgram(GeoShaderProgram);

	const GLint WidthPosition{ glGetUniformLocation(GeoShaderProgram, "w") };
	glUniform1f(WidthPosition, (GLfloat)(ScreenWidth));

	const GLint HeightPosition{ glGetUniformLocation(GeoShaderProgram, "h") };
	glUniform1f(HeightPosition, (GLfloat)(ScreenHeight));
}

void RenderGeoShader()
{
	waveOutGetPosition(WaveOut, &MMTime, sizeof(MMTIME));
	const GLint TimePosition{ glGetUniformLocation(GeoShaderProgram, "t") };
	glUniform1f(TimePosition, (float)(MMTime.u.sample));

	// Get BassDrum note (int = 46) MIDI Channel 3
	constexpr int Channel{ 2 };
	const int BassDrumNote{ (&_4klang_note_buffer)[((MMTime.u.sample >> 8) << 5) + Channel * 2] };

	const GLint BassDrumPosition{ glGetUniformLocation(GeoShaderProgram, "bd") };
	glUniform1f(BassDrumPosition, (float)(BassDrumNote));
}