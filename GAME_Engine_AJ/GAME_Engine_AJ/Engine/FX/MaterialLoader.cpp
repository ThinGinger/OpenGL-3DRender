#include "MaterialLoader.h"

void MaterialLoader::LoadMaterial(std::string file_)
{
	std::ifstream in(file_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open MTL file: " + file_, __FILE__, __LINE__);
		return;
	}
	//If all goes well then...
	Material m = Material();
	std::string matName = "";
	std::string line;
	while (std::getline(in, line)) {
		//if you're reading a line right now read from position 0 to 7
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(matName, m);
				m = Material(); //resetting it's variable.
			}
			//name of the material from position 7 till the end of the line.
			matName = line.substr(7); 
			m.diffuseMap = LoadTexture(matName);
		}

		//Ns - shininess TODO
		else if (line.substr(0, 4) == "\tNs ") {
				std::istringstream Ns(line.substr(3));
				Ns >> m.shininess;
		}

		//d - transparancy TODO
		else if (line.substr(0, 4) == "\td ") {
			std::istringstream d(line.substr(3));
			d >> m.transparency;
		}

		//ka - ambient TODO
		else if (line.substr(0, 4) == "\tka ")
		{
			std::istringstream Ka(line.substr(3));
			Ka >> m.ambient.x >> m.ambient.y >> m.ambient.z;
		}

		//Kd - diffuse TODO
		else if (line.substr(0, 4) == "\tKd ")
		{
			std::istringstream Ka(line.substr(3));
			Ka >> m.diffuse.x >> m.diffuse.y >> m.diffuse.z;
		}

		//Ks - specular TODO
		else if (line.substr(0, 4) == "\tKs ")
		{
			std::istringstream Ka(line.substr(3));
			Ka >> m.specular.x >> m.specular.y >> m.specular.z;
		}

	}

	//When you're done looking though the m file
	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(matName, m);
	}
}

GLuint MaterialLoader::LoadTexture(std::string fileName_)
{
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(fileName_, "Resources/Textures/" + fileName_ + ".jpg");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}

