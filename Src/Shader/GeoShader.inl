// I´m using string literals ("R") here; so we don´t have to add "\n" at the end of each line and the code is much easier to read and maintain.
// You also need a delimiter, it´s "D" here. But you can choose freely.

const char* GeoSource = R"D(
	#version 450 core

	layout(location = 0) uniform float t;
	layout(location = 1) uniform float w;
	layout(location = 2) uniform float h;
	layout(location = 3) uniform float bd;

	out vec4 outColor;

	vec3 f(vec3 p)
	{
		p *= .1;

		for (int i = 0; i < 5; ++i)
		{
			p = abs(fract((p.yzx * mat3(.8, .6, .0, -.6, .8, .0, .0, .0, 1.)) + vec3(.123, .456, .789) * float(i)) - .5) * 2.;
		}

		p *= p;
		return sqrt(p + p.yzx) * .33;
	}

	void main()
	{
		vec2 r = vec2(w, h);
		vec3 d = vec3((gl_FragCoord.xy - r.xy * .5) / r.x, 1.), p = vec3(.5, .8, t / 22050.), c;

		for (int i = 0; i < 50; ++i)
		{
			vec3 f2 = f(p + bd * .001);
			p += d * min(min(f2.x, f2.y), f2.z);
			c += float(50 - i) / (f2 + .005);
		}

		c = vec3(1. - 1. / (1. + c * (-.06 * .0004)));
		c *= c;

		outColor = vec4(c.r * 6., .0, bd * .007, 1.);
	}
)D";