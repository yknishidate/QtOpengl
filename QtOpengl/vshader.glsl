#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform mat4 projMatrix;
uniform mat4 mvMatrix;
//uniform mat4 normalMatrix;

out vec4 vColor;

void main(){
  gl_Position = projMatrix * mvMatrix * vec4(position, 1.0);
  //vColor = vec4(position+vec3(0.25f), 1.0);
  vColor = vec4(color, 1.0f);
}
