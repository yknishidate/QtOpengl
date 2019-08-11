#version 330
//layout(location = 0) in vec3 position;
in vec3 position;
out vec4 vColor;
uniform mat4 mvMatrix;
uniform mat4 projMatrix;
//uniform mat4 normalMatrix;

void main(){
  //gl_Position = vec4(position.x, position.y, position.z, 1.0);
  gl_Position = /*projMatrix **/ mvMatrix * vec4(position.x, position.y, position.z, 1.0);;
  vColor = vec4(position.y, position.x, 0.2-position.x, 1.0);
}
