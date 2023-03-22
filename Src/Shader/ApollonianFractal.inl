// I´m using string literals ("R") here; so we don´t have to add "\n" at the end of each line and the code is much easier to read and maintain.
// You also need a delimiter, it´s "D" here. But you can choose freely.

const char* ApollonianFractalSource = R"D(
	#version 450 core

	layout(location = 0) uniform float t;
	layout(location = 1) uniform float w;
	layout(location = 2) uniform float h;
	layout(location = 3) uniform float sd;
	layout(location = 4) uniform float bd;

	out vec4 outColor;

    float Sphere(vec3 p, int f)
    {
        p.z += t * .00001;
        float s = 1.;

        for (int i = 0; i < f; ++i)
        {
            float k = 1.7 / dot(p = mod(p - 1., 2.) - 1., p);
            p *= k;
            s *= k;
        }

        return length(p) / s;
    }

    void main()
    {
        float ti = t * .000005;
        vec2 res = vec2(w, h);
        vec3 uv = vec3(gl_FragCoord.xy / res.y - .5, 1.) * .25;
        vec3 r = vec3(1., 1., ti);
        vec2 m = sin(vec2(.0, 1.5) + ti);

        uv.xy = mat2(m.y, -m.x, m) * uv.xy;
        uv.xz = mat2(m.y, -m.x, m) * uv.xz;

        outColor -= outColor;

        int f = 4;

        if (sd != .0)
        {
            f = 8;
        }

        for (outColor.w; outColor.w < 40.; ++outColor.w)
        {
            r += Sphere(r, f) * uv;
        }

        outColor += Sphere(r, f) * Sphere(r - uv, f) * (40. + bd);
        outColor.bg *= 8. * uv.xz;
    }
)D";