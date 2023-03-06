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
}