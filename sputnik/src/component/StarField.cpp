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
	TriangleMesh* stars = generator::generateStars(1200.0f, 1.5f, 80000);
	
	std::string mediaPath = props->getString(types::symbolize("media-path"));
	
	Shader* shader = new Shader(mediaPath + "shaders/base.vert", mediaPath + "shaders/stars.frag");
	
	mesh = new RenderMesh21(stars, shader);
}

void StarField::onRender(RenderPass pass, Camera *camera)
{
	UNUSED pass;
	mesh->draw(camera, glm::mat4(1));
}
