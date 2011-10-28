#include "Generator.hpp"

#include <kocmoc-core/scene/TriangleMesh.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace sputnik::scene;
using namespace kocmoc::core::scene;

using namespace glm;


TriangleMesh* generator::generateStars(float domain, float starSize,
									   unsigned int count)
{
	unsigned int primitiveCount = count * 4; // 3 tris per tetraeder
	unsigned int vertexIndexCount = primitiveCount * 3; // 3 vertices per triangle
	unsigned int vertexCount = count * 4; // 4 vertices per tetraeder
	
	float *positions = new float[vertexCount * 3];
	unsigned int *vertexIndices = new unsigned int[vertexIndexCount];
	
	glm::mat4 scale = glm::gtx::transform::scale(starSize, starSize, starSize);
	
	for (unsigned int i = 0; i < count; i++)
	{
		vec4 v0 = vec4(0, 0, 0, 1);
		vec4 v1 = vec4(0, 1, 1, 1);
		vec4 v2 = vec4(1, 1, 0, 1);
		vec4 v3 = vec4(1, 0, 1, 1);
		
		mat4 rotation = glm::gtx::transform::rotate(((float)rand() * 360)/RAND_MAX,
													(float)rand() / RAND_MAX,
													(float)rand() / RAND_MAX,
													(float)rand() / RAND_MAX);
		
		vec3 translation = vec3((rand() * domain) / RAND_MAX - (domain / 2),
								(rand() * domain) / RAND_MAX - (domain / 2),
								(rand() * domain) / RAND_MAX - (domain / 2));
		
		mat4 transform = glm::translate(translation) * scale * rotation;
		
		v0 = transform * v0;
		v1 = transform * v1;
		v2 = transform * v2;
		v3 = transform * v3;
		
		// ad vertices
		positions[i*12] = v0.x;
		positions[i*12+1] = v0.y;
		positions[i*12+2] = v0.z;
		positions[i*12+3] = v1.x;
		positions[i*12+4] = v1.y;
		positions[i*12+5] = v1.z;
		positions[i*12+6] = v2.x;
		positions[i*12+7] = v2.y;
		positions[i*12+8] = v2.z;
		positions[i*12+9] = v3.x;
		positions[i*12+10] = v3.y;
		positions[i*12+11] = v3.z;
		
		
		// add primitives and indices, 
		// 0 - 1 - 2
		vertexIndices[i*12] = i*4;
		vertexIndices[i*12+1] = i*4 +1;
		vertexIndices[i*12+2] = i*4 +2;
		
		//3 - 2 - 1
		vertexIndices[i*12+3] = i*4 +3;
		vertexIndices[i*12+4] = i*4 +2;
		vertexIndices[i*12+5] = i*4 +1;
		
		//1 - 0 - 3
		vertexIndices[i*12+6] = i*4 +1;
		vertexIndices[i*12+7] = i*4 +0;
		vertexIndices[i*12+8] = i*4 +3;
		
		// 0 - 2 - 3
		vertexIndices[i*12+9] = i*4 +0;
		vertexIndices[i*12+10] = i*4 +2;
		vertexIndices[i*12+11] = i*4 +3;
	}
	
	return new TriangleMesh(count * 12, vertexIndices, count * 4, positions);
}