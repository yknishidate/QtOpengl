#version 330
layout(location = 0)in vec3 position;
layout(location = 1)in vec2 texcoord;
layout(location = 2)in vec3 normal;
uniform mat4 projMatrix;
uniform mat4 mMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;
uniform mat3 viewMatrix;
out vec4 P;
out vec3 N;
out vec2 vTexcoord;
//----------Test----------
out vec4 vPosition;
out vec4 vNormal;
out vec4 vColor;
//----------Test----------

void main(){
  vPosition   = (mMatrix * vec4(position, 1.0));
  vNormal     = (mMatrix * vec4(normal, 0.0));
  P = mvMatrix * vec4(position, 1.0);   //カメラ座標のPosition
  N = normalize(normalMatrix * normal); //ワールド座標のNormal
  vTexcoord = texcoord;
  gl_Position = projMatrix * P;         //スクリーン座標
}

//----------Test----------
//vPosition   = (mMatrix * vec4(position, 1.0));
//vNormal     = (mMatrix * vec4(normal, 0.0));
//vColor      = vec4(0.5);
//gl_Position = projMatrix * mvMatrix * vec4(position, 1.0);
//----------Test----------
