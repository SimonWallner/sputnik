#include "TextLabel.hpp"

#include <kocmoc-core/scene/FontRenderer.hpp>
#include <kocmoc-core/renderer/Shader.hpp>

using namespace kocmoc::core::scene;
using namespace kocmoc::core::component;
using namespace kocmoc::core::renderer;
using namespace kocmoc::core::types;

using namespace sputnik::component;

using std::string;
using glm::vec2;

void TextLabel::init()
{	
	const float size = 3;
	
	objectBehaviour = parent->getComponent<ObjectBehaviour>();
	
	FontRenderer fontRenderer(props, size * 40, size * 4);
	Tex tex = fontRenderer.render(text);
	
	string mediaPath = props->getString(symbolize("media-path"));
	Shader* shader = new Shader(mediaPath+ "shaders/textLabel.vert",
					   mediaPath + "shaders/textLabel.frag");
	
	quad = new Quad(shader, tex.handle);
	quad->init();	
	quad->setSize(vec2((tex.width / tex.height) * size, size));
}

void TextLabel::onUpdate(float deltaT, float t)
{
	UNUSED deltaT;
	UNUSED t;
	quad->setPosition(objectBehaviour->position);
	quad->setRotation(objectBehaviour->rotation);
}

void TextLabel::onRender(RenderPass pass, Camera *camera)
{
	quad->draw(camera);
	UNUSED pass;
}
