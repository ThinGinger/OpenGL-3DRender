#include "Square.h"



Square::Square(GLuint shaderProgram_, GLuint textureID_) : Model(shaderProgram_)
{

	Vertex v;
	std::vector<Vertex> vertexList;

	//Triangle 1
	v.position = glm::vec3(-0.5f, 0.5f, 0.0f);

	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);


	//Triangle 2
	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);

	// Dont forget to Add Mesh
	AddMesh(new Mesh(&vertexList, textureID_, shaderProgram_));
}


Square::~Square()
{
}
