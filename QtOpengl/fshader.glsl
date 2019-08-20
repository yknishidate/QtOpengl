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

vec3 Lpos = vec3(5.0f, 10.0f, 5.0f);
vec3 Lamb = vec3(0.2f, 0.2f, 0.2f);

void main(){
    if(wire == 0){
        if(textureSample == 0){
            diffColor = vec4(Kdiff * max(dot(N, normalize(Lpos)), 0) + Kamb*Lamb , 1.0f) ;
            //diffColor = vec4(Kdiff, 1.0f);
        }else{
            diffColor = vec4(texture2D(texture, vTexcoord).xyz * max(dot(N, normalize(Lpos)), 0) + texture2D(texture, vTexcoord).xyz*Lamb, 1.0f) ;
            //diffColor = texture2D(texture, vTexcoord);
        }
        fColor = diffColor;
    }else{
        fColor = vec4(0.1f, 0.1f, 0.1f, 1.0f);
    }

}
