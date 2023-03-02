#include "./Shader/GeoShader.inl"

GLuint GeoShaderProgram{};

void LoadGeoShader()
{
	GeoShaderProgram = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &GeoSource);
	glUseProgram(GeoShaderProgram);

	const GLint WidthPosition{ glGetUniformLocation(GeoShaderProgram, "Width") };
	glUniform1f(WidthPosition, (GLfloat)(ScreenWidth));

	const GLint HeightPosition{ glGetUniformLocation(GeoShaderProgram, "Height") };
	glUniform1f(HeightPosition, (GLfloat)(ScreenHeight));
}

void RenderGeoShader()
{
	static float TimeElapsed{};
	TimeElapsed += 0.06F;
	const GLint TimeElapsedPosition{ glGetUniformLocation(GeoShaderProgram, "TimeElapsed") };
	glUniform1f(TimeElapsedPosition, TimeElapsed);
}