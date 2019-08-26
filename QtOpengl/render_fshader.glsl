#version 430
//uniform sampler2D srcTex;
layout(binding = 1) uniform sampler2D scene_tex;
in vec2 texCoord;
out vec4 color;
void main() {
    //color = vec4(texture(srcTex, texCoord));
    color = vec4(texture(scene_tex, texCoord));
}
