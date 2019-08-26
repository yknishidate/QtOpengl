#version 430
in vec2 pos;
out vec2 texCoord;
void main() {
     texCoord = pos*0.5f + 0.5f; //0-1に正規化
     gl_Position = vec4(pos, 0.0, 1.0);
}
