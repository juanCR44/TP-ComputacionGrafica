#version 330 core
layout (location = 0) in vec3 pPosicion;
layout (location = 1) in vec3 pColor;
out vec4 color_vertice;
void main(){
	gl_Position = vec4(pPosicion, 1.0);
	color_vertice = vec4(pColor, 1.0);
}