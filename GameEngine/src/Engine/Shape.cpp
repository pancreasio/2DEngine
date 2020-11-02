#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shape.h"
#include "LoadShader.h"
#include "Texture.h"

Shape::Shape()
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	static const GLfloat g_vertex_buffer_data[] = {
		1.f, -1.f, 0.0f, 1.0f, 1.f, 1.0f, 1.0f, 0.0f,//+-
		-1.f, 1.f, 0.0f, 1.0f, 1.f, 1.0f, 0.0f, 1.0f,//-+
		-1.f, -1.f, 0.0f, 1.0f, 1.f, 1.0f, 0.0f, 0.0f,//--
		1.f, 1.f, 0.0f, 1.0f, 1.f, 1.0f, 1.0f, 1.0f,//++  
	};

	// Create a Vertex Buffer Object and copy the vertex data to it
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint elements[] =
	{
		0, 1, 2, 3
	};

	// Create an element array
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

}

Shape::Shape(glm::vec3 pos, glm::vec3 setScale, Texture* tex) : Entity(pos, tex)
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	scale = setScale;

	posVertex[0] = { -1.f * setScale.x / 2, 1.f * setScale.y / 2, 0.0f };
	posVertex[1] = { 1.f * setScale.x / 2, 1.f * setScale.y / 2, 0.0f };
	posVertex[2] = { -1.f * setScale.x / 2, -1.f * setScale.y / 2, 0.0f };
	posVertex[3] = { 1.f * setScale.x / 2, -1.f * setScale.y / 2, 0.0f };

	colorVertex[0] = { 1.f, 1.f, 1.f };
	colorVertex[1] = { 1.f, 1.f, 1.f };
	colorVertex[2] = { 1.f, 1.f, 1.f };
	colorVertex[3] = { 1.f, 1.f, 1.f };

	texVertex[0] = { 0.f, 1.f };
	texVertex[1] = { 1.f,1.f };
	texVertex[2] = { 0.f,0.f };
	texVertex[3] = { 1.f,0.f };


	const GLfloat g_vertex_buffer_data[] =
	{
		posVertex[0].x, posVertex[0].y, posVertex[0].z, colorVertex[0].x, colorVertex[0].y, colorVertex[0].z, texVertex[0].x, texVertex[0].y,
		posVertex[1].x, posVertex[1].y, posVertex[1].z, colorVertex[1].x, colorVertex[1].y, colorVertex[1].z, texVertex[1].x, texVertex[1].y,
		posVertex[2].x, posVertex[2].y, posVertex[2].z, colorVertex[2].x, colorVertex[2].y, colorVertex[2].z, texVertex[2].x, texVertex[2].y,
		posVertex[3].x, posVertex[3].y, posVertex[3].z, colorVertex[3].x, colorVertex[3].y, colorVertex[3].z, texVertex[3].x, texVertex[3].y
	};

	// Create a Vertex Buffer Object and copy the vertex data to it
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint elements[] =
	{
		0, 1, 2, 3
	};

	glUseProgram(programID);

	// Create an element array
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	GLuint posAttrib = glGetAttribLocation(programID, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	GLuint colAttrib = glGetAttribLocation(programID, "customColor");
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(colAttrib);

	GLuint texAttrib = glGetAttribLocation(programID, "aTexCoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

}

Shape::~Shape()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glDeleteBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ebo);
	glDeleteBuffers(1, &ebo);
}
