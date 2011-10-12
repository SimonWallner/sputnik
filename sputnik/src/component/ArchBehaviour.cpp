#include <component/ArchBehaviour.hpp>

#include <iostream>

#include <kocmoc-core/renderer/RenderMesh.hpp>
#include <kocmoc-core/scene/AssetLoader.hpp>
#include <kocmoc-core/util/Properties.hpp>
#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/component/Renderable.hpp>

using namespace sputnik::component;

using kocmoc::core::renderer::RenderPass;
using kocmoc::core::renderer::RenderPass;
using kocmoc::core::scene::Camera;
using kocmoc::core::scene::AssetLoader;
using kocmoc::core::component::Renderable;
using kocmoc::core::util::Properties;
using kocmoc::core::types::symbolize;

ArchBehaviour::ArchBehaviour(Properties* _props, unsigned int _instanceCount)
	: props(_props)
	, instanceCount(_instanceCount)
	, start(glm::vec3(0))
	, end(glm::vec3(0, 0, -20))
{};

void ArchBehaviour::onRender(RenderPass pass, Camera *camera)
{	
	if (pass == kocmoc::core::renderer::RP_NORMAL)
	{
		instancedMesh->setShaderParam("start", start);
		instancedMesh->setShaderParam("end", end);
		instancedMesh->drawInstanced(camera, glm::mat4(1), instanceCount);
	}
}

void ArchBehaviour::init()
{
	AssetLoader loader;
	loader.addResourcePath(props->getString(symbolize("media-path")));
	loader.addResourcePath(props->getString(symbolize("core-media-path")));
	std::string test = props->getString(symbolize("arch-model-name"));
	std::string shaderPath = props->getString(symbolize("media-path")) + "shaders/arch";
	
	// FIXME: something mutates my stirngs in the props.
	// changing it here to c_str() helped, but it is evil
	// XXX:
#warning XXX: problem with mutable strings in props!
	Renderable* renderable = loader.load(test.c_str(), shaderPath);
	instancedMesh = renderable->getFirstMesh();
}
