#version 330 core
out vec4 Color;
in vec2 Textura;
in  vec4 color_vertice;
uniform sampler2D ourTexture;
void main(){

	Color = texture(ourTexture, Textura);
}
