#version 330
#extension GL_NV_shadow_samplers_cube : enable
const float M_PI = 3.1415926535897932384626433832795;
uniform int textureSample;
uniform int wire;
uniform bool outline;
uniform int materialType;
uniform sampler2D texture;

in vec4 P;
in vec3 N;
in vec2 vTexcoord;

// Material
uniform vec3 Kamb;
uniform vec3 Kdiff;
uniform vec3 Kspec;
uniform float Kshi;
// Light
uniform vec3 Lpos =  vec3(100.0f, 100.0f, 100.0f);
uniform vec3 Ldiff = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 Lamb  = vec3(0.1f, 0.1f, 0.1f);
uniform vec3 Lspec = vec3(1.0f, 1.0f, 1.0f);

// Result
out vec4 fColor;

//----------Test----------
uniform samplerCube cubeTexture;
in vec4        vPosition;
//----------Test----------

void main(){
    vec3 diffuse = vec3(0);
    vec3 specular = vec3(0);

    if(wire == 1){
        fColor = vec4(0.2f, 0.2f, 0.2f, 1.0f);
    }else if(outline){
        fColor = vec4(1, 0.75, 0.2, 1);
    }else{
        switch(materialType){
        case 0: //Diffuse
            vec3 V = -normalize(P.xyz);
            vec3 L = normalize(Lpos-P.xyz);
            vec3 H = normalize(L + V);
            float norFac = ((Kshi+2.0f)*(Kshi+4.0f))/(8*M_PI*(pow(2, -Kshi/2)) + Kshi); //正規化係数

            if(textureSample == 0){
                diffuse  +=  max(dot(N, L), 0)               * Kdiff * Ldiff + Kamb * Lamb ;
                specular +=  pow(max(dot(normalize(N), H), 0.0), Kshi)  * Kspec * Lspec * norFac/100.0f;
            }else{
                vec3 texColor = texture2D(texture, vTexcoord).xyz;
                diffuse += texColor * Ldiff * max(dot(N, L), 0) + texColor*Lamb;
                specular +=  pow(max(dot(normalize(N), H), 0.0), Kshi)  * Kspec * Lspec * norFac/100.0f;
            }
            fColor = vec4(diffuse + specular, 1.0f);
            break;
        case 1: //Metal
            vec3 ref = reflect(-normalize(P.xyz), N);
            fColor   = textureCube(cubeTexture, ref);
            break;
        case 2: // Glass
            fColor = vec4(0.6);
            break;
        case 3: // Light
            fColor = vec4(1);
            break;
        }
    }
}
