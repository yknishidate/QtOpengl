#version 330
//layout(location = 0) in vec3 position;
//layout(location = 1) in vec3 color;
layout(location = 0)in vec3 position;
layout(location = 1)in vec2 texcoord;
layout(location = 2)in vec3 normal;
uniform mat4 projMatrix;
uniform mat4 mvMatrix;
//uniform mat4 normalMatrix;

out vec4 vColor;
out vec2 vTexcoord;

void main(){
  gl_Position = projMatrix * mvMatrix * vec4(position, 1.0);
  //vColor = vec4(position+vec3(0.25f), 1.0);
  //vColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  vTexcoord = texcoord;
}
