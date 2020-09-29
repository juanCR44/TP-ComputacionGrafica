
#version 330 core
layout (location = 0) in vec3 pPosicion;
layout (location = 1) in vec3 pColor;
layout (location = 2) in vec2 pTextura;
out vec4 color_vertice;
out vec2 Textura;
uniform mat4 transformacion;
void main(){
	gl_Position = transformacion * vec4(pPosicion, 1.0);
	color_vertice = vec4(pColor, 1.0);
	Textura = vec2(pTextura);
	//gl_Position = vec4(pPosicion, 1.0) + vec4(traslacion, 0.0);
	//gl_Position = vec4(pPosicion, 1.0);
}
