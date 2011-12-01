
//  Kocmoc.cpp
//  kocmoc
//
//  Created by Simon Wallner on 28.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Sputnik.hpp"

#include <iostream>
#include <string>

#include <glm/gtx/quaternion.hpp>

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
#include <component/PulseSize.hpp>

#include <object/Text.hpp>
#include <object/Arc.hpp>
#include <object/Sampler.hpp>
#include <object/Player.hpp>
#include <object/TapeMachine.hpp>
#include <object/WayPoint.hpp>
#include <object/WeightTest.hpp>

#include <scene/SelectableWorld.hpp>
#include <output/MIDIout.hpp>


using namespace sputnik;
using namespace kocmoc::core::types;
using namespace kocmoc::core::input;
using namespace kocmoc::core::component;
using namespace kocmoc::core::renderer;
using namespace kocmoc::core::scene;

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
using glm::gtx::quaternion::angleAxis;


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
	

//#warning FIXME: context somehow fucks up working directory, therfore must be after config file loading
	// this only occurs in the Xcode debugger, not when build with make and run
	// from the command line.
	context = new Context(props);
	context->getInfo();

	
	string mediaPath = props->getString(symbolize("media-path"));
	string coreMediaPath = props->getString(symbolize("core-media-path"));

	
	// ---------- SPLASH ----------------
	OrthoCamera splashCamera(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0));
	splashCamera.setWidthHeightDepth(width/2.0f, height/2.0f, 1.0f);
	splashCamera.updateMatrixes();
	
	FontRenderer fontRenderer(props, 100);
	Tex tex = fontRenderer.render("sputnik");

	Shader startShader(coreMediaPath + "shaders/overlay.vert",
					   coreMediaPath + "shaders/text.frag");
	
	OverlayQuad start(props, &startShader, tex.handle);
	start.setScale(vec2(tex.width, tex.height));
	start.setPosition(vec2((tex.width >> 1) * -1.0f, (tex.height >> 1) * -1.0f + 10));
	start.init();
	
	FontRenderer smallFont(props, 30);
	Tex small = smallFont.render("press 1 & 2 on your controller");
	OverlayQuad smallQuad(props, &startShader, small.handle);
	smallQuad.setScale(vec2(small.width, small.height));
	smallQuad.setPosition(vec2((small.width >> 1) * -1.0f, -130.0f));
	smallQuad.init();
	
	
	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	start.onRender(RP_OVERLAY, &splashCamera);
	smallQuad.onRender(RP_OVERLAY, &splashCamera);
	context->swapBuffers();
	
	
	
	
	
	input::WiimoteInputManager inputManager(context->getWindowHandle());
	
	inputManager.registerButtonEventListener(quit, &ic);
	inputManager.bindKeyToButtonEvent(256, quit);	// ESC
	inputManager.bindWiimoteEvent(WIIMOTE_EVENT_BUTTON_MINUS_HELD, quit);

	inputManager.registerButtonEventListener(screenShot, &ic);
	inputManager.bindKeyToButtonEvent(',', screenShot);
	
	
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
	
	
	
	// ------------------- CONTENT ------------------------------------------
	
	SelectableWorld selectableWorld;
	
	Arc arc(props, &inputManager, camera, &selectableWorld);
	
	MIDIOut* mOut = new MIDIOut();
	
	Sampler sampler("\"Space achievment, ...\"", props, &selectableWorld, &inputManager, mOut, 1);
	sampler.setPosition(vec3(24.5f, 0.0f, -19.5f));
	
	Sampler sampler2("\"adventure\"", props, &selectableWorld, &inputManager,mOut, 3);
	sampler2.setPosition(vec3(-19.0f, 4.5f, -50));
	sampler2.setRotation(angleAxis(10.0f, -1.0f, 1.0f, -1.0f));
	
	Sampler sampler3("\"I believe, we should go to the moon!\"", props, &selectableWorld, &inputManager,mOut, 5);
	sampler3.setPosition(vec3(-10.0f, -13.5f, -46.5f));
	sampler3.setRotation(angleAxis(40.0f, 0.2f ,0.8f, 0.2f));
	
	Sampler sampler4("\"sputnik\"", props, &selectableWorld, &inputManager,mOut, 7);
	sampler4.setPosition(vec3(23.5f, 12.0f, -23.0f));
	sampler4.setRotation(angleAxis(-90.0f, 0.0f ,1.0f, 0.0f));
	
	
	
	Player player("break!", props, &selectableWorld, &inputManager, mOut, 10);
	player.setPosition(vec3(-17, -31, -40));
	player.setRotation(angleAxis(-30.0f, 1.0f, 0.0f, 0.0f));
	
	TapeMachine tapeMachine("JFK", props, &selectableWorld, mOut, 50);
	tapeMachine.setPosition(vec3(-43, 25, -19));
	tapeMachine.setRotation(angleAxis(60.0f, 0.0f, 1.0f, 0.1f));
	
	
	
	WayPoint wayPoint1(props, &selectableWorld, mOut, 21);
	wayPoint1.setPosition(vec3(-13, -10, -19));
	PulseSize pulse1(1.0f, 1.2f, 0.5f, 0.0f);
	wayPoint1.addComponent(&pulse1);
	wayPoint1.registerUpdateReceiver(&pulse1);
	pulse1.init();
	
	WayPoint wayPoint2(props, &selectableWorld, mOut, 22);
	wayPoint2.setPosition(vec3(-18, -8, -19));
	PulseSize pulse2(1.0f, 1.2f, 0.5f, 1.0f);
	wayPoint2.addComponent(&pulse2);
	wayPoint2.registerUpdateReceiver(&pulse2);
	pulse2.init();

	WayPoint wayPoint3(props, &selectableWorld, mOut, 23);
	wayPoint3.setPosition(vec3(-23, -5, -19));
	PulseSize pulse3(1.0f, 1.2f, 0.5f, 2.0f);
	wayPoint3.addComponent(&pulse3);
	wayPoint3.registerUpdateReceiver(&pulse3);
	pulse3.init();
	
	WayPoint wayPoint4(props, &selectableWorld, mOut, 24);
	wayPoint4.setPosition(vec3(-28, -1, -19));
	PulseSize pulse4(1.0f, 1.2f, 0.5f, 3.0f);
	wayPoint4.addComponent(&pulse4);
	wayPoint4.registerUpdateReceiver(&pulse4);
	pulse4.init();
	
	WayPoint wayPoint5(props, &selectableWorld, mOut, 25);
	wayPoint5.setPosition(vec3(-33, 5, -19));
	PulseSize pulse5(1.0f, 1.2f, 0.5f, 4.0f);
	wayPoint5.addComponent(&pulse5);
	wayPoint5.registerUpdateReceiver(&pulse5);
	pulse5.init();
	
	WayPoint wayPoint6(props, &selectableWorld, mOut, 26);
	wayPoint6.setPosition(vec3(-38, 13, -19));
	PulseSize pulse6(1.0f, 1.2f, 0.5f, 5.0f);
	wayPoint6.addComponent(&pulse6);
	wayPoint6.registerUpdateReceiver(&pulse6);
	pulse6.init();
	
	
	WeightTest wt1("1.0", props, vec3(0, 0, 40), 1.0f, &selectableWorld);
	WeightTest wt2("0.5", props, vec3(-10, 0, 40), 0.5f, &selectableWorld);
	WeightTest wt3("2.0", props, vec3(-20, 0, 40), 2.0f, &selectableWorld);
	WeightTest wt4("1.5", props, vec3(-30, 0, 40), 1.5f, &selectableWorld);
	
	
	
	
	StarField starField(props);
	starField.init();
	
	Text text1(props, "user study, mid december!");
	text1.setPosition(vec3(50, 20, -150));
	text1.setRotation(angleAxis(-30.f, 0.0f, 1.0f, 0.0f));
	text1.update(0, 0);

	Text text2(props, "@SimonWallner");
	text2.setPosition(vec3(50, 17, -150));
	text2.setRotation(angleAxis(-30.f, 0.0f, 1.0f, 0.0f));
	text2.update(0, 0);
	
	Text text3(props, "http://simonwallner.at");
	text3.setPosition(vec3(50, 14, -150));
	text3.setRotation(angleAxis(-30.f, 0.0f, 1.0f, 0.0f));
	text3.update(0, 0);
	
	
	
	
					  
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
	
	Timer* timer = new Timer(context->getWindowHandle());
	
	while (running == true && context->isAlive())
	{	
		// pre update
		timer->tick();
		timer->print();
		float deltaT = timer->getDeltaT();
		float t = timer ->getLastT();
		
		
		cameraController.onUpdate(deltaT);
		wiimoteCameraController.onUpdate(deltaT);
		
		inputManager.poll();
		inputManager.pollWiimote();
		
		// update
		sampler.update(deltaT, t);
		sampler2.update(deltaT, t);
		sampler3.update(deltaT, t);
		sampler4.update(deltaT, t);
		
		player.update(deltaT, t);
		tapeMachine.update(deltaT, t);
		
		wayPoint1.update(deltaT, t);
		wayPoint2.update(deltaT, t);
		wayPoint3.update(deltaT, t);
		wayPoint4.update(deltaT, t);
		wayPoint5.update(deltaT, t);
		wayPoint6.update(deltaT, t);
		
		wt1.update(deltaT, t);
		wt2.update(deltaT, t);
		wt3.update(deltaT, t);
		wt4.update(deltaT, t);
		
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
			sampler2.render(RP_NORMAL, camera);
			sampler3.render(RP_NORMAL, camera);
			sampler4.render(RP_NORMAL, camera);
			
			player.render(RP_NORMAL, camera);
			tapeMachine.render(RP_NORMAL, camera);
			
			wayPoint1.render(RP_NORMAL, camera);
			wayPoint2.render(RP_NORMAL, camera);
			wayPoint3.render(RP_NORMAL, camera);
			wayPoint4.render(RP_NORMAL, camera);
			wayPoint5.render(RP_NORMAL, camera);
			wayPoint6.render(RP_NORMAL, camera);
			
			wt1.render(RP_NORMAL, camera);
			wt2.render(RP_NORMAL, camera);
			wt3.render(RP_NORMAL, camera);
			wt4.render(RP_NORMAL, camera);
			
			
			text1.render(RP_NORMAL, camera);
			text2.render(RP_NORMAL, camera);
			text3.render(RP_NORMAL, camera);
			
			starField.onRender(RP_NORMAL, camera);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			arc.render(RP_NORMAL, camera);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		
		// draw framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, width, height);
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
