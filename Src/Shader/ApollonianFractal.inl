// I´m using string literals ("R") here; so we don´t have to add "\n" at the end of each line and the code is much easier to read and maintain.
// You also need a delimiter, it´s "D" here. But you can choose freely.

const char* ApollonianFractalSource = R"D(
	#version 450 core

	layout(location = 0) uniform float t;
	layout(location = 1) uniform float w;
	layout(location = 2) uniform float h;
	layout(location = 3) uniform float bd;
	layout(location = 4) uniform float sd;

	out vec4 outColor;

    float Sphere(vec3 p)
    {
        p.z += t * .00003;
        float s = 1.;

        for (int i = 0; i < 4; ++i)
        {
            float k = 1.7 / dot(p = mod(p - 1., 2.) - 1., p);
            p *= k;
            s *= k;
        }

        return length(p) / s;
    }


    void main()
    {
        float ti = t * .00001;
        vec2 res = vec2(w, h);
        vec3 uv = vec3(gl_FragCoord.xy / res.y - .5, 1.) * .25;
        vec3 r = vec3(1., 1., ti);
        vec2 m = sin(vec2(.0, 1.5) + ti);

        uv.xy = mat2(m.y, -m.x, m) * uv.xy;
        uv.xz = mat2(m.y, -m.x, m) * uv.xz;

        outColor -= outColor;

        for (outColor.w; outColor.w < 40.; ++outColor.w)
        {
            r += Sphere(r) * uv;
        }

        outColor += Sphere(r) * Sphere(r - uv) * 40.;
        outColor.bg *= 8. * uv.xz;
    }
)D";