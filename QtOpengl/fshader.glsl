#version 330
uniform int textureSample;
uniform int wire;
uniform sampler2D texture;
in vec4 vColor;
in vec2 vTexcoord;

in vec3 N;

out vec4 fColor;

uniform vec3 Kamb;
uniform vec3 Kdiff;
uniform vec3 Kspec;
uniform float Kshi;

vec4 diffColor;

vec3 Lpos = vec3(50.0f, 100.0f, 80.0f);
vec3 Lamb = vec3(0.2f, 0.2f, 0.2f);

void main(){
    if(wire == 0){
        if(textureSample == 0){
            diffColor = vec4(Kdiff * max(dot(N, normalize(Lpos)), 0) + Kamb*Lamb , 1.0f) ;
        }else{
            vec3 texColor = texture2D(texture, vTexcoord).xyz;
            diffColor = vec4(texColor * max(dot(N, normalize(Lpos)), 0) + texColor*Lamb, 1.0f) ;
        }
        fColor = diffColor;
    }else{
        fColor = vec4(0.2f, 0.2f, 0.2f, 1.0f);
    }

}
