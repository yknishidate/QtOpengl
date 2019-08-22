#version 330
const float M_PI = 3.1415926535897932384626433832795;
uniform int textureSample;
uniform int wire;
uniform sampler2D texture;
in vec2 vTexcoord;

//in vec3 L;
in vec4 P;
in vec3 N;

out vec4 fColor;
//Material
uniform vec3 Kamb;
uniform vec3 Kdiff;
uniform vec3 Kspec;
uniform float Kshi;
//Light
uniform vec3 Lpos =  vec3(100.0f, 100.0f, 100.0f);
uniform vec3 Ldiff = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 Lamb  = vec3(0.1f, 0.1f, 0.1f);
uniform vec3 Lspec = vec3(1.0f, 1.0f, 1.0f);


void main(){
    vec3 diffuse;
    vec3 specular = vec3(0);
    if(wire == 0){
        vec3 V = -normalize(P.xyz);
        vec3 L = normalize(Lpos-P.xyz);
        vec3 H = normalize(L + V);
        //float norFac = ((Kshi+2.0f)*(Kshi+4.0f))/(8*M_PI*(pow(2, -Kshi/2)) + Kshi);

        if(textureSample == 0){
            // Sun Light
            //diffuse = Kdiff * Ldiff * max(dot(N, normalize(Lpos)), 0) + Kamb * Lamb ;
            // Point Light
            diffuse  =  max(dot(N, L), 0)               * Kdiff * Ldiff + Kamb * Lamb ;
            specular =  pow(max(dot(N, H), 0.0), Kshi)  * Kspec * Lspec;
        }else{
            vec3 texColor = texture2D(texture, vTexcoord).xyz;
            diffuse = texColor * Ldiff * max(dot(N, L), 0) + texColor*Lamb;
            specular =  pow(max(dot(N, H), 0.0), Kshi)  * Kspec * Lspec;
        }
        fColor = vec4(diffuse + specular, 1.0f);
    }else{
        fColor = vec4(0.2f, 0.2f, 0.2f, 1.0f);
    }
}
