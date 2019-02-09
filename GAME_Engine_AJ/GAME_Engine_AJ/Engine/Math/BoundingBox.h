#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/glm.hpp>

struct BoundingBox {

	glm::vec3 minVert;
	glm::vec3 maxVert;
	glm::mat4 transform;

	inline BoundingBox() {

		minVert = glm::vec3(0.0f);
		maxVert = glm::vec3(0.0f);
		transform = glm::mat4(0.0f);

	}

	inline BoundingBox(glm::vec3 minVert_, glm::vec3 maxVert_, glm::mat4 transform_) {
		minVert = minVert_;
		maxVert = maxVert_;
		transform = transform_;
	}
};

#endif // !BOUNDINGBOX_H
