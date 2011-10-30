
//  Kocmoc.cpp
//  kocmoc
//
//  Created by Simon Wallner on 28.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Sputnik.hpp"

#include <iostream>
#include <string>

#include <kocmoc-core/util/Properties.hpp>
#include <kocmoc-core/util/util.hpp>
#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/renderer/Shader.hpp>
#include <kocmoc-core/renderer/FrameBuffer21.hpp>
#include <kocmoc-core/component/OverlayQuad.hpp>
#include <kocmoc-core/input/InputManager.hpp>
#include <kocmoc-core/scene/FilmCamera.hpp>
#include <kocmoc-core/scene/OrthoCamera.hpp>
#include <kocmoc-core/scene/FontRenderer.hpp>
#include <kocmoc-core/time/Timer.hpp>
#include <kocmoc-core/component/CameraController.hpp>


#include <kocmoc-core/gl.h>


#include <component/WiimoteDebugger.hpp>
#include <component/WiimoteCameraController.hpp>
#include <component/StarField.hpp>
#include <object/Arc.hpp>
#include <object/Sampler.hpp>
#include <scene/SelectableWorld.hpp>

using namespace sputnik;
using namespace kocmoc::core::types;
using namespace kocmoc::core::input;
using namespace kocmoc::core::component;
using namespace kocmoc::core::renderer;

using namespace sputnik::component;
using namespace sputnik::object;
using namespace sputnik::scene;

using std::string;

using kocmoc::core::util::Properties;
using kocmoc::core::renderer::Context;
using kocmoc::core::renderer::Shader;
using kocmoc::core::renderer::FrameBuffer21;
using kocmoc::core::scene::FilmCamera;
using kocmoc::core::scene::OrthoCamera;
using kocmoc::core::time::Timer;
using kocmoc::core::scene::FontRenderer;


using sputnik::output::MIDIOut;

using glm::vec3;
using glm::vec2;


Sputnik::Sputnik(Properties* _props)
	: props(_props)
	, running(true)
	, quit(symbolize("quit"))
	, screenShot(symbolize("screen-shot"))
	, note(symbolize("note"))
	, cursorX(symbolize("cursor-x"))
	, ic(this)
{
	string configFile = props->getString(symbolize("config-file"));
	string coreConfigFile = props->getString(symbolize("core-config-file"));
	kocmoc::core::util::parser::parseConfigXMLFileIntoProperties(configFile, props);
	kocmoc::core::util::parser::parseConfigXMLFileIntoProperties(coreConfigFile, props);
	props->dumpCache();

	int width = props->getFloat(symbolize("width"));
	int height = props->getFloat(symbolize("height"));
	

#warning FIXME: context somehow fucks up working directory, therfore must be after config file loading
	// this only occurs in the Xcode debugger, not when build with make and run
	// from the command line.
	context = new Context(props);
	context->getInfo();
	
	input::WiimoteInputManager inputManager(context->getWindowHandle());
	
	inputManager.registerButtonEventListener(quit, &ic);
	inputManager.bindKeyToButtonEvent(256, quit);	// ESC
	inputManager.bindWiimoteEvent(WIIMOTE_EVENT_BUTTON_MINUS_HELD, quit);

	inputManager.registerButtonEventListener(screenShot, &ic);
	inputManager.bindKeyToButtonEvent(',', screenShot);
	
	
	monkey = new Monkey("it's a duck!", props, &inputManager);
	
//	FontRenderer fontRenderer(props);
//	fontRenderer.render("P.AY");
	
	
	WiimoteDebugger wiimoteDebugger0("wiimote debugger 0", props, &inputManager, 0);
	wiimoteDebugger0.init();
	WiimoteDebugger wiimoteDebugger1("wiimote debugger 1", props, &inputManager, 1);
	wiimoteDebugger1.init();	
	
	OrthoCamera overlayCamera(vec3(width/2.0f, height/2.0f, 0), vec3(0, 0, -1), vec3(0, 1, 0));
	overlayCamera.setWidthHeightDepth(width/2.0f, height/2.0f, 1.0f);
	overlayCamera.updateMatrixes();
	
	FilmCamera* camera = new FilmCamera(vec3(0, 0, 4), vec3(0, 0, 0), vec3(0, 1, 0));
	camera->setGateInPixel(width, height);
	camera->setFilterMarginInPixel(0, 0);
	camera->setAngleOfView(2.0f);
	camera->updateMatrixes();
	
	
	FrameBuffer21* frameBuffer = new FrameBuffer21(width * 1.1f, height * 1.1f,
												   width, height,
												   width, height,
												   camera->getAngleOfView(),
												   props);
	
	
	SelectableWorld selectableWorld;
	
	Arc arc(props, &inputManager, camera, &selectableWorld);
	Sampler sampler("Sampler one", props, &selectableWorld);
	
	StarField starField(props);
	starField.init();
	
	string mediaPath = props->getString(symbolize("media-path"));
	Shader clearShader(mediaPath + "shaders/clear.vert",
					   mediaPath + "shaders/clear.frag");
	OverlayQuad background(props, &clearShader);
	background.setPosition(vec2(-1.0f, -1.0f));
	background.setScale(vec2(2.0f, 2.0f));
	background.init();
	
	
	CameraController cameraController(camera, &inputManager);
	WiimoteCameraController wiimoteCameraController(camera, &inputManager, props);
	camera->tumble(0.1f, 0.1f);
	
	inputManager.dumpBindings();	
	
	Timer* timer = new Timer();
	
	while (running == true && context->isAlive())
	{	
		// pre update
		timer->tick();
		float deltaT = timer->getDeltaT();
		float t = timer ->getLastT();
		
		cameraController.onUpdate(deltaT);
		wiimoteCameraController.onUpdate(deltaT);
		
		inputManager.poll();
		inputManager.pollWiimote();
		
		// update
		monkey->update(deltaT, t);
		
		
		// post update
		camera->updateMatrixes();
		
		// MRT setup
		GLenum buffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};

		
		// -------------------- rendering ---------------------------
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer->getFBOHandle());
		glViewport(0, 0, frameBuffer->frameWidth, frameBuffer->frameHeight);
		{
			// render normal
			glDrawBuffers(2, buffers);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glDepthMask(GL_FALSE);
			background.onRender(RP_OVERLAY, NULL);
			glDepthMask(GL_TRUE);

			sampler.render(RP_NORMAL, camera);
			starField.onRender(RP_NORMAL, camera);

			
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			arc.render(RP_NORMAL, camera);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		
		// draw framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		frameBuffer->drawFBO();
		
		// render overlays
		wiimoteDebugger0.render(RP_OVERLAY, &overlayCamera);
		wiimoteDebugger1.render(RP_OVERLAY, &overlayCamera);
		
		// post render
		context->swapBuffers();
	}
}

void Sputnik::printIntro()
{
	std::cout	<< "//////////////////////////////////////////////////////////////////////////////" << std::endl
	<< "   *           .                          .                          .        " << std::endl
	<< "                             .                   .                         " << std::endl
	<< "           .                                                    *           " << std::endl  
	<< ".                                        .                               " << std::endl 
	<< "                    .              .                  .                 .        " << std::endl
	<< "                                                                      " << std::endl
	<< "                                                                             " << std::endl
	<< "         .           *                      .                 .                " << std::endl
	<< "                               .           *                                   " << std::endl
	<< "                                                                         .    " << std::endl
	<< "                      .             .                         .                 " << std::endl
	<< "*          .                                                                   " << std::endl
	<< "                                                 .         0                   " << std::endl
	<< "                             .                            /|\\                    " << std::endl
	<< "          .                                                           .        " << std::endl
	<< "                                                .                             " << std::endl
	<< "                     *               .                    .                     " << std::endl
	<< "   .                                                                 *         " << std::endl
	<< "                                      .                                       " << std::endl
	<< "//// sputnik //////////////////////////////////////////////////////////////////" << std::endl;
}

Sputnik::~Sputnik()
{
	std::cout << "destroying kocmoc" << std::endl;
}
