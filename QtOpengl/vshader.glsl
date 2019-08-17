#version 330
layout(location = 0)in vec3 position;
layout(location = 1)in vec2 texcoord;
layout(location = 2)in vec3 normal;
uniform mat4 projMatrix;
uniform mat4 mvMatrix;
//uniform mat4 normalMatrix;

out vec4 vColor;
out vec4 gridColor;
out vec2 vTexcoord;

void main(){
  gl_Position = projMatrix * mvMatrix * vec4(position, 1.0);
  gridColor = vec4(0.8f);
  vTexcoord = texcoord;
}
