#pragma once

#include <string>
#include "math/vec3.h"
#include "color.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram
{
public:
	ShaderProgram();

	ShaderProgram(unsigned int ID);

	void use();

	unsigned int id() const;

	void setBool(std::string uniformName, bool val);

	void setFloat(std::string uniformName, float val);

	void setInt(std::string uniformName, int val);

	void setVec3(std::string uniformName, math::Vec3 val);

	void setColor(std::string uniformName, shading::Color val);

	void setColor3(std::string uniformName, shading::Color val);

	void setMat4(std::string uniformName, glm::mat4 val);

private:
	unsigned int _ID;
};