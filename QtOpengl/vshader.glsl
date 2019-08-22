#version 330
layout(location = 0)in vec3 position;
layout(location = 1)in vec2 texcoord;
layout(location = 2)in vec3 normal;
uniform mat4 projMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;
out vec4 P;
out vec3 N;
out vec2 vTexcoord;

void main(){
  P = mvMatrix * vec4(position, 1.0);   //カメラ座標のPosition
  N = normalize(normalMatrix * normal); //ワールド座標のNormal
  vTexcoord = texcoord;
  gl_Position = projMatrix * P;         //スクリーン座標
}
