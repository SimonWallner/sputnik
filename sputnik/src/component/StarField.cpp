#include "StarField.hpp"

#include <scene/Generator.hpp>

#include <kocmoc-core/compiler.h>

using namespace sputnik::component;
using namespace sputnik::scene;
using namespace kocmoc::core::scene;
using namespace kocmoc::core::renderer;
using namespace kocmoc::core;

void StarField::init()
{
	TriangleMesh* stars = generator::generateStars(1000.0f, 2.0f, 10000);
	
	std::string coreMediaPath = props->getString(types::symbolize("core-media-path"));
	std::string sputnikMediaPath = props->getString(types::symbolize("media-path"));
	
	Shader* shader = new Shader(coreMediaPath + "shaders/base.vert", sputnikMediaPath + "shaders/stars.frag");
	
	mesh = new RenderMesh21(stars, shader);
}

void StarField::onRender(RenderPass pass, Camera *camera)
{
	UNUSED pass;
	mesh->draw(camera, glm::mat4(1));
}