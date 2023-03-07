const char* GeoSource =
"#version 450 core\n"

"layout(location = 0) uniform float t;\n"
"layout(location = 1) uniform float w;\n"
"layout(location = 2) uniform float h;\n"
"layout(location = 3) uniform float bd;\n"

"out vec4 outColor;\n"

"vec3 f(vec3 p)\n"
"{\n"
	"p *= .1;\n"

	"for (int i = 0; i < 5; ++i)\n"
	"{\n"
		"p = abs(fract((p.yzx * mat3(.8, .6, .0, -.6, .8, .0, .0, .0, 1.)) + vec3(.123, .456, .789) * float(i)) - .5) * 2.;\n"
	"}\n"

	"p *= p;\n"
	"return sqrt(p + p.yzx) * .33;\n"
"}\n"

"void main()\n"
"{\n"
	"vec2 r = vec2(w, h);\n"
	"vec3 d = vec3((gl_FragCoord.xy - r.xy * .5) / r.x, 1.), p = vec3(.5, .8, t / 22050.), c;\n"

	"for (int i = 0; i < 50; ++i)\n"
	"{\n"
		"vec3 f2 = f(p + bd * .001);\n"
		"p += d * min(min(f2.x, f2.y), f2.z);\n"
		"c += float(50 - i) / (f2 + .005);\n"
	"}\n"

	"c = vec3(1. - 1. / (1. + c * (-.06 * .0004)));\n"
	"c *= c;\n"

	"outColor = vec4(c.r * 6., .0, bd * .007, 1.);\n"
"}";