const char* GeoSource =
"#version 450 core\n"
"precision mediump float;\n"

"uniform float TimeElapsed;\n"
"uniform float Width;\n"
"uniform float Height;\n"

"out vec4 outColor;\n"

"vec2 Resolution = vec2(Width, Height);\n"

"vec3 Field(vec3 Pos)\n"
"{\n"
	"Pos *= 0.1;\n"
	"float f = 0.1;\n"

	"for (int i = 0; i < 5; ++i)\n"
	"{\n"
		"Pos = (Pos.yzx * mat3(0.8, 0.6, 0, -0.6, 0.8, 0.0, 0.0, 0.0, 1.0)) + vec3(0.123, 0.456, 0.789) * float(i);\n"
		"Pos = (abs(fract(Pos) - 0.5)) * 2.0;\n"
		"f *= 2.0;\n"
	"}\n"

	"Pos *= Pos;\n"
	"return sqrt(Pos + Pos.yzx) / f + 0.0001;\n"
"}\n"

"void main()\n"
"{\n"
	"vec3 Direction = vec3((gl_FragCoord.xy - Resolution.xy * 0.5) / Resolution.x, 1.0);\n"
	"vec3 Position = vec3(0.5, 0.8, (TimeElapsed / 22050.0F));\n"
	"vec3 Color;\n"

	"for (int i = 0; i < 50; ++i)\n"
	"{\n"
		"vec3 f2 = Field(Position);\n"
		"Position += Direction * min(min(f2.x, f2.y), f2.z);\n"
		"Color += float(50 - i) / (f2 + 0.005);\n"
	"}\n"

	"Color = vec3(1.0 - 1.0 / (1.0 + Color * (-0.06 / 2500.0)));\n"
	"Color *= Color;\n"
	"outColor = vec4(Color.r * 6.0, 0.0, 0.0, 1.0);\n"
"}";