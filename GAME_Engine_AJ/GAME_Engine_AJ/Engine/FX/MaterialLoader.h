#ifndef MATERIALLOADER_H
#define MATERIALLOADER_H

#include "../Graphics/MaterialHandler.h"
#include "../Graphics/TextureHandler.h"
#include <sstream>

class MaterialLoader
{
public:
	MaterialLoader() = delete; //if you try to create another instance of material loader it won't let you.
	MaterialLoader(const MaterialLoader&) = delete;
	MaterialLoader(MaterialLoader&&) = delete;
	MaterialLoader& operator = (const MaterialLoader&) = delete;
	MaterialLoader& operator = (MaterialLoader&&) = delete;

	static void LoadMaterial(std::string file_);
	static GLuint LoadTexture(std::string fileName_);
};

#endif // !MATERIALLOADER_H

