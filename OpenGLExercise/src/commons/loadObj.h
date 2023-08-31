#pragma once
#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
struct OBJModel
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;
};

struct OBJModelIndexed : public OBJModel
{
	std::vector<unsigned short> indices;
};

OBJModel loadOBJ(const std::string& path, bool computeTangents = false);

static bool readObjFile(
	const char* path,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals
);
