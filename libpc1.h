#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;
unsigned int id_array_vertices, id_array_buffers, id_element_buffer;
unsigned int texture;
int width, height, nrChannels;

class LibPc1 {
private:
	int vertex_count = 0;
	int face_count = 0;
	int edge_count = 0;
	int flotanes = 0;
	char floats = 0;
	int LINE = 3;
	//Vertices
	float* vertices = 0;
	float varx = 0;
	float vary = 0;
	float varz = 0;
	float f1 = 0;
	float f2 = 0;
	float f3 = 0;

	//Faces
	int* faces = 0;
	int nVertices = 0;
	int indexv1 = 0;
	int indexv2 = 0;
	int indexv3 = 0;
public:
	float xmin = 1e09, xmax = -1e09, ymin = 1e09, ymax = -1e09, zmin = 1e09, zmax = -1e09;

	void leerOFF(const char* nombre) {
		ifstream MyReadFile1(nombre);
		string line;
		for (int i = 1; i <= LINE; i++)
			getline(MyReadFile1, line);
		//cout << line << endl;
		for (int i = 0; i < line.size(); i++) {

			if (line[i] == ' ') flotanes++;

		}
		//cout << flotanes << endl;
		MyReadFile1.close();

		ifstream MyReadFile(nombre);
		string name;
		//Primera linea
		MyReadFile >> name;
		cout << name << "\n";
		//Segunda linea
		MyReadFile >> vertex_count >> face_count >> edge_count;
		//getline(MyReadFile, line);
		//cout << line << "\n";
		//flotanes = vertex_count;
		//MyReadFile.get(floats);

		cout << vertex_count << face_count << edge_count << flotanes << "\n";
		//Sin color ni textura
		if (flotanes == 3)
			vertices = new float[vertex_count * 3];
		//Color
		if (flotanes == 6)
			vertices = new float[vertex_count * 6];
		//Textura
		if (flotanes == 5)
			vertices = new float[vertex_count * 5];

		faces = new int[face_count * 3];

		for (int i = 0; i < vertex_count; i++)
		{
			if (flotanes == 3) {
				MyReadFile >> varx >> vary >> varz;

				if (varx < xmin)	xmin = varx;
				if (varx > xmax)	xmax = varx;
				if (vary < ymin)	ymin = vary;
				if (vary > ymax)	ymax = vary;
				if (varz < zmin)	zmin = varz;
				if (varz > zmax)	zmax = varz;

				vertices[3 * i] = varx;
				vertices[3 * i + 1] = vary;
				vertices[3 * i + 2] = varz;

			}
			//Color
			if (flotanes == 6) {
				MyReadFile >> varx >> vary >> varz >> f1 >> f2 >> f3;

				if (varx < xmin)	xmin = varx;
				if (varx > xmax)	xmax = varx;
				if (vary < ymin)	ymin = vary;
				if (vary > ymax)	ymax = vary;
				if (varz < zmin)	zmin = varz;
				if (varz > zmax)	zmax = varz;

				vertices[6 * i] = varx;
				vertices[6 * i + 1] = vary;
				vertices[6 * i + 2] = varz;
				vertices[6 * i + 3] = f1;
				vertices[6 * i + 4] = f2;
				vertices[6 * i + 5] = f3;
			}
			//Texturas
			if (flotanes == 5) {
				MyReadFile >> varx >> vary >> varz >> f1 >> f2;

				if (varx < xmin)	xmin = varx;
				if (varx > xmax)	xmax = varx;
				if (vary < ymin)	ymin = vary;
				if (vary > ymax)	ymax = vary;
				if (varz < zmin)	zmin = varz;
				if (varz > zmax)	zmax = varz;

				vertices[5 * i] = varx;
				vertices[5 * i + 1] = vary;
				vertices[5 * i + 2] = varz;
				vertices[5 * i + 3] = f1;
				vertices[5 * i + 4] = f2;
			}
		}

		for (int i = 0; i < face_count; i++)
		{
			MyReadFile >> nVertices >> indexv1 >> indexv2 >> indexv3;
			//cout <<" "<< varx << " " << vary << " " << varz << "\n";
			faces[3 * i] = indexv1;
			faces[3 * i + 1] = indexv2;
			faces[3 * i + 2] = indexv3;
		}

		MyReadFile.close();
	}

	void generateTexture(const char* nombre) {
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
		unsigned char* data = stbi_load(nombre, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}

	void drawTexture() {
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	void setGeometry() {
		glGenVertexArrays(1, &id_array_vertices);
		glGenBuffers(1, &id_array_buffers);
		glGenBuffers(1, &id_element_buffer);


		//anexando los buffers para su uso en la tarjeta gráfica
		glBindVertexArray(id_array_vertices);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_element_buffer);

		//Anexando buffers y cargandolos con los datos
		if (flotanes == 3) {
			glBindBuffer(GL_ARRAY_BUFFER, id_array_buffers);
			glBufferData(GL_ARRAY_BUFFER, vertex_count * 3 * sizeof(float), vertices, GL_STATIC_DRAW);
		}
		//Color
		if (flotanes == 6) {
			glBindBuffer(GL_ARRAY_BUFFER, id_array_buffers);
			glBufferData(GL_ARRAY_BUFFER, vertex_count * 6 * sizeof(float), vertices, GL_STATIC_DRAW);
		}
		//Textura
		if (flotanes == 5) {
			glBindBuffer(GL_ARRAY_BUFFER, id_array_buffers);
			glBufferData(GL_ARRAY_BUFFER, vertex_count * 5 * sizeof(float), vertices, GL_STATIC_DRAW);
		}

		if (face_count > 0) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_element_buffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_count * 3 * sizeof(int), faces, GL_STATIC_DRAW);
		}

		//Indicando las especificaciones de los atributos
		if (flotanes == 3) {
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
		}
		//Color
		if (flotanes == 6) {
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
		}
		//Textura
		if (flotanes == 5) {
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(2);
		}
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float)));
		//glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void drawElement() {
		if (face_count > 0) {
			glBindVertexArray(id_array_vertices);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_element_buffer);
			glDrawElements(GL_TRIANGLES, face_count * 3, GL_UNSIGNED_INT, 0);
		}
		else {
			glBindVertexArray(id_array_vertices);
			glDrawArrays(GL_TRIANGLES, 0, vertex_count);
		}
	}

	void translateCenter(glm::mat4& transformacion) {
		transformacion = glm::translate(transformacion, glm::vec3(-(xmax + xmin) / 2.0f, -(ymax + ymin) / 2.0f, -(zmax + zmin) / 2.0f));
	}

	void translateTo(glm::mat4& transformacion, float x, float y, float z) {
		transformacion = glm::translate(transformacion, glm::vec3(x, y, z));
	}

	void scale(glm::mat4& transformacion, float x, float y, float z) {
		transformacion = glm::scale(transformacion, glm::vec3(x, y, z));
	}

	void rotate(glm::mat4& transformacion, int factor, float x, float y, float z) {
		transformacion = glm::rotate(transformacion, (float)glfwGetTime() * factor, glm::vec3(x, y, z));
	}


	void liberarMemoria() {
		glDeleteVertexArrays(1, &id_array_vertices);
		glDeleteBuffers(1, &id_array_buffers);
	}

	float* getVertices() {
		return this->vertices;
	}
	int* getFaces() {
		return this->faces;
	}

	int getVertexCount() {
		return this->vertex_count;
	}

	int getFacesCount() {
		return this->face_count;
	}

	int getEdgesCount() {
		return this->edge_count;
	}
};