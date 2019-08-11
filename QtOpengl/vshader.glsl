#version 330
layout(location = 0) in vec3 position;
uniform mat4 projMatrix;
uniform mat4 mvMatrix;
//uniform mat4 normalMatrix;
out vec4 vColor;

void main(){
  gl_Position = projMatrix * mvMatrix * vec4(position, 1.0);;
  vColor = vec4(position.y, position.x, 0.2-position.x, 1.0);
}
