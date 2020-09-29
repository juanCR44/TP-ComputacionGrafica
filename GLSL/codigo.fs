

#version 330 core
out vec4 Color;
in vec2 Textura;
//uniform  vec4 color_vertice;
in  vec4 color_vertice;
uniform sampler2D ourTexture;
void main(){
	//Color = vec4(1.0, 1.0, 0.0, 0.0);
	//Color = color_vertice;
	Color = texture(ourTexture, Textura);
}
