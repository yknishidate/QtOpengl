#version 330
uniform sampler2D texture;
in vec4 vColor;
in vec2 vTexcoord;
out vec4 fColor;

void main(){
    //fColor = vColor;
    fColor = texture2D(texture, vTexcoord);;
}
