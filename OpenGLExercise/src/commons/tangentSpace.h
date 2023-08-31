#pragma once

#include <glm/glm.hpp>

#include <vector>

void computeTangentBasis(
	// inputs
	const std::vector<glm::vec3>& vertices,
	const std::vector<glm::vec2>& uvs,
	const std::vector<glm::vec3>& normals,
	// outputs
	std::vector<glm::vec3>& tangents,
	std::vector<glm::vec3>& bitangents
);

