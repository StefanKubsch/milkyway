// I´m using string literals ("R") here; so we don´t have to add "\n" at the end of each line and the code is much easier to read and maintain.
// You also need a delimiter, it´s "D" here. But you can choose freely.
const char* ApollonianFractalSource = R"D(
#version 450
layout(location=0) uniform float t;
layout(location=1) uniform float h;
layout(location=2) uniform float s;
layout(location=3) uniform float b;
out vec4 o;
float sp(vec3 p,int f){p.z+=t*.000007;float s=1;for(int i=0;i<f;++i){float k=1.7/dot(p=mod(p-1,2)-1,p);p*=k;s*=k;}return length(p)/s;}
void main(){
vec3 u=vec3(gl_FragCoord.xy/h-.5,1)*.25,r=vec3(1,1,t*.000007);
vec2 m=sin(vec2(0,1.5)+t*.000007);
u.xy=mat2(m.y,-m.x,m)*u.xy;
u.xz=mat2(m.y,-m.x,m)*u.xz;
o=vec4(0);
int f=4;
if(s!=0)f=8;
for(o.a;o.a<40;++o.a)r+=sp(r,f)*u;
o+=sp(r,f)*sp(r-u,f)*(40+b);
o.bg*=8*u.xz;}
)D";