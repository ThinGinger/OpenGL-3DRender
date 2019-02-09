#include "LoadOBJModel.h"



LoadOBJModel::LoadOBJModel() : currentMaterial(Material())
{

}


LoadOBJModel::~LoadOBJModel()
{
	vertices.clear();
	vertices.shrink_to_fit();

	normals.clear();
	normals.shrink_to_fit();

	textureCoords.clear();
	textureCoords.shrink_to_fit();

	indices.clear();
	indices.shrink_to_fit();

	normalIndices.clear();
	normalIndices.shrink_to_fit();

	textureIndices.clear();
	textureIndices.shrink_to_fit();

	meshVertices.clear();
	meshVertices.shrink_to_fit();

	meshes.clear();
	meshes.shrink_to_fit();
}


void LoadOBJModel::LoadModel(const std::string& fileName_) {
	std::ifstream in(fileName_, std::ios::in);
	if (!in) {
		Debug::Error("Cannot Load OBJ File:" + fileName_, __FILE__, __LINE__);
		return;
	}
	std::string line;
	while (std::getline(in, line)) {
		// VERTEX DATA
		if (line.substr(0, 2) == "v ") {
			std::istringstream v(line.substr(2));
			double x, y, z;
			v >> x >> y >> z;

			if (boundingBox.minVert.x == 0 || boundingBox.minVert.x > x)
			{
				boundingBox.minVert.x = x;
			}
			if (boundingBox.minVert.y == 0 || boundingBox.minVert.y > y)
			{
				boundingBox.minVert.y = y;
			}
			if (boundingBox.minVert.z == 0 || boundingBox.minVert.z > z)
			{
				boundingBox.minVert.z = z;
			}

			if (boundingBox.maxVert.x < x)
			{
				boundingBox.maxVert.x = x;
			}
			if (boundingBox.maxVert.y < y)
			{
				boundingBox.maxVert.y = y;
			}
			if (boundingBox.maxVert.z < z)
			{
				boundingBox.maxVert.z = z;
			}

			
			vertices.push_back(glm::vec3(x, y, z)); //take the new x y z and push it the vertices vector
		}
		//NORMAL DATA
		else if (line.substr(0, 3) == "vn ") {
			std::istringstream vn(line.substr(3));
			double x, y, z;
			vn >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z)); //take the new x y z and push it the vertices vector
		}

		//TEXTURE COORDINATE DATA
		else if (line.substr(0, 3) == "vt ") {
			std::istringstream vt(line.substr(3));
			double x, y;
			vt >> x >> y;
			textureCoords.push_back(glm::vec2(x, y));
		}

		//FACE DATA
		///(vertex/texture/normal) position / texture / normal  p/t/n  p/t/n   they are indices

		else if (line.substr(0, 2) == "f ") {
			std::istringstream f(line.substr(2));

			char slash; //omit the slash
			int x, y, z;

				f >> x >> slash >> y >> slash >> z;

				indices.push_back(GLuint(x));
				textureIndices.push_back(GLuint(y));
				normalIndices.push_back(GLuint(z));

				f >> x >> slash >> y >> slash >> z;

				indices.push_back(GLuint(x));
				textureIndices.push_back(GLuint(y));
				normalIndices.push_back(GLuint(z));

				f >> x >> slash >> y >> slash >> z;

				indices.push_back(GLuint(x));
				textureIndices.push_back(GLuint(y));
				normalIndices.push_back(GLuint(z));

		}

		//MATERIAL DATA
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}

	}
	PostProcessing();
}
void LoadOBJModel::LoadModel(const std::string& fileName_, const std::string& matName_) {
	LoadMaterialLibrary(matName_);
	LoadModel(fileName_);
}

std::vector<Vertex> LoadOBJModel::GetVerts() {
	return meshVertices;
}

std::vector<GLuint> LoadOBJModel::GetIndices() {
	return indices;
}

std::vector<SubMesh> LoadOBJModel::GetMeshes() {
	return meshes;
}

void LoadOBJModel::PostProcessing() {

	for (unsigned int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = vertices[indices[i] - 1 ]; //minus it by 1
		vert.normal = normals[normalIndices[i] - 1]; //minus it by 1
		vert.texCoords = textureCoords[textureIndices[i] - 1]; // minus it by 1
		meshVertices.push_back(vert);

	}
	SubMesh mesh;

	mesh.vertexList = meshVertices;
	mesh.indices = indices;
	mesh.material = currentMaterial;
	meshes.push_back(mesh);

	indices.clear();
	indices.shrink_to_fit();

	normalIndices.clear();
	normalIndices.shrink_to_fit();

	textureIndices.clear();
	textureIndices.shrink_to_fit();

	meshVertices.clear();
	meshVertices.shrink_to_fit();

	currentMaterial = Material();

}

void LoadOBJModel::LoadMaterial(const std::string& fileName_) {
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(fileName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matName_) {
	MaterialLoader::LoadMaterial(matName_);
}

BoundingBox LoadOBJModel::GetBoundingBox()
{
	return boundingBox;
}
