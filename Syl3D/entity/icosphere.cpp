#include "icosphere.h"

using namespace entity;

IcoSphere::IcoSphere(int recursionLevel, std::string shaderName)
	:
	Entity(shaderName),
	_sphere(std::make_shared<mesh::IcoSphereMesh>(recursionLevel))
{
	this->initialize({ std::static_pointer_cast<mesh::Mesh>(_sphere) });
}

IcoSphere::IcoSphere(math::Vec3 startingPos, int recursionLevel, std::string shaderName)
	:
	IcoSphere(recursionLevel, shaderName)
{
	_pos = startingPos;
}

void IcoSphere::draw() {
	if (_usesEBO) {
		glBindVertexArray(_VAOs[0]);
		glDrawElements(GL_TRIANGLES, _sphere->numIndices() / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	}
}