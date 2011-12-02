
//  Kocmoc.cpp
//  kocmoc
//
//  Created by Simon Wallner on 28.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Sputnik.hpp"

#include <iostream>
//#include <string>

#include <glm/gtx/quaternion.hpp>

// wrap, wrap
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <glm/gtx/spline.hpp>
//#pragma GCC diagnostic error "-Wunused-variable" // stupid c++ templates!!!



#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/input/InputManager.hpp>
#include <kocmoc-core/time/Timer.hpp>

#include <kocmoc-core/util/Properties.hpp>
#include <kocmoc-core/util/util.hpp>

#include <kocmoc-core/renderer/Shader.hpp>
#include <kocmoc-core/renderer/FrameBuffer21.hpp>

#include <kocmoc-core/component/OverlayQuad.hpp>
#include <kocmoc-core/component/CameraController.hpp>

#include <kocmoc-core/scene/OrthoCamera.hpp>
#include <kocmoc-core/scene/FontRenderer.hpp>
#include <kocmoc-core/scene/AssetLoader.hpp>

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
using glm::gtx::spline::catmullRom;


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
	
	camera = new FilmCamera(vec3(0, 0, 4), vec3(0, 0, 0), vec3(0, 1, 0));
	camera->setGateInPixel(width, height);
	camera->setFilterMarginInPixel(0, 0);
	camera->setAngleOfView(2.0f);
	camera->updateMatrixes();
	
	
	FrameBuffer21* frameBuffer = new FrameBuffer21(width * 1.1f, height * 1.1f,
												   width, height,
												   width, height,
												   camera->getAngleOfView(),
												   props);
	
	
	
	// ------------------- CONTENT -----------------------------------------
	
	assetLoader = new AssetLoader();
	assetLoader->addResourcePath(props->getString(symbolize("media-path")));

	
	SelectableWorld selectableWorld;
	
	Arc arc(props, &inputManager, camera, &selectableWorld);
	
	MIDIOut* mOut = new MIDIOut();
	
	// -- tier 1 ---------------------------------------
	
	Sampler sampler("\"Space achievment, ...\"", this, &selectableWorld, &inputManager, mOut, 1);
	sampler.setPosition(vec3(24.5f, 0.0f, -19.5f));
	
	Sampler sampler2("\"adventure\"", this, &selectableWorld, &inputManager,mOut, 2);
	sampler2.setPosition(vec3(-19.0f, 4.5f, -50));
	sampler2.setRotation(angleAxis(10.0f, -1.0f, 1.0f, -1.0f));
	
	Sampler sampler3("\"I believe, we should go to the moon!\"", this, &selectableWorld, &inputManager,mOut, 3);
	sampler3.setPosition(vec3(-10.0f, -13.5f, -46.5f));
	sampler3.setRotation(angleAxis(40.0f, 0.2f ,0.8f, 0.2f));
	
	Sampler sampler4("\"sputnik\"", this, &selectableWorld, &inputManager,mOut, 4);
	sampler4.setPosition(vec3(23.5f, 12.0f, -23.0f));
	sampler4.setRotation(angleAxis(-90.0f, 0.0f ,1.0f, 0.0f));
	
	
	
	Player player("break!", this, &selectableWorld, &inputManager, mOut, 6);
	player.setPosition(vec3(-17, -31, -40));
	player.setRotation(angleAxis(-30.0f, 1.0f, 0.0f, 0.0f));
	
	TapeMachine tapeMachine("JFK", this, &selectableWorld, mOut, 12);
	tapeMachine.setPosition(vec3(-43, 25, -19));
	tapeMachine.setRotation(angleAxis(60.0f, 0.0f, 1.0f, 0.1f));
	
	
	unsigned int wpCount = 20;
	WayPoint** section1 = new WayPoint*[wpCount];
	vec3 wp0 = vec3(100, 0, -19);
	vec3 wp1 = vec3(-13, -10, -19);
	vec3 wp2 = vec3(-200, -50, -19);
	vec3 wp3 = vec3(-210, -500, -1000);
	
	for (unsigned int i = 0; i < wpCount; i++)
	{
		vec3 pos = catmullRom(wp0, wp1, wp2, wp3, (float)i/wpCount);
		section1[i] = new WayPoint(this, &selectableWorld, mOut, 60+i);
		section1[i]->setPosition(pos);
		
//		PulseSize* pulse = new PulseSize(1.0f, 2.0f, 1.0f, i);
//		section1[i]->addComponent(pulse);
//		section1[i]->registerUpdateReceiver(pulse);
//		pulse->init();
	}
	
	
	WayPoint** section2 = new WayPoint*[wpCount];
	vec3 wp4 = vec3(-100, 0, -19);
	vec3 wp5 = vec3(13, -10, -19);
	vec3 wp6 = vec3(200, 33, -19);
	vec3 wp7 = vec3(210, 500, -1000);
	
	for (unsigned int i = 0; i < wpCount; i++)
	{
		vec3 pos = catmullRom(wp4, wp5, wp6, wp7, (float)i/wpCount);
		section2[i] = new WayPoint(this, &selectableWorld, mOut, 80+i);
		section2[i]->setPosition(pos);
	}
	
	
	// -- tier 2 ---------------------------------------------------------
	Sampler samplerT21("\"Space achievment, ...\"", this, &selectableWorld, &inputManager, mOut, 21);
	samplerT21.setPosition(vec3(-180.0f, -50.0f, -19.5f));
	
	Sampler samplerT22("\"adventure\"", this, &selectableWorld, &inputManager,mOut, 22);
	samplerT22.setPosition(vec3(-219.0f, -45.0f, -50));
	samplerT22.setRotation(angleAxis(10.0f, -1.0f, 1.0f, -1.0f));
	
	Sampler samplerT23("\"I believe, we should go to the moon!\"", this, &selectableWorld, &inputManager,mOut, 23);
	samplerT23.setPosition(vec3(-210.0f, -63.5f, -46.5f));
	samplerT23.setRotation(angleAxis(40.0f, 0.2f ,0.8f, 0.2f));
	
	Sampler samplerT24("\"sputnik\"", this, &selectableWorld, &inputManager,mOut, 24);
	samplerT24.setPosition(vec3(-180.0f, -38.0f, -23.0f));
	samplerT24.setRotation(angleAxis(-90.0f, 0.0f ,1.0f, 0.0f));
	
	
	Player playerT2("break!", this, &selectableWorld, &inputManager, mOut, 26);
	playerT2.setPosition(vec3(-190, -81, -40));
	playerT2.setRotation(angleAxis(-30.0f, 1.0f, 0.0f, 0.0f));
	
	
	// -- tier 3 ---------------------------------------
	
	Sampler samplerT31("\"Space achievment, ...\"", this, &selectableWorld, &inputManager, mOut, 41);
	samplerT31.setPosition(vec3(224.5f, 2.0f, -19.5f));
	
	Sampler samplerT32("\"adventure\"", this, &selectableWorld, &inputManager,mOut, 42);
	samplerT32.setPosition(vec3(180.0f, 24.5f, -50));
	samplerT32.setRotation(angleAxis(10.0f, -1.0f, 1.0f, -1.0f));
	
	Sampler samplerT33("\"I believe, we should go to the moon!\"", this, &selectableWorld, &inputManager,mOut, 43);
	samplerT33.setPosition(vec3(190.0f, -6.5f, -46.5f));
	samplerT33.setRotation(angleAxis(40.0f, 0.2f ,0.8f, 0.2f));
	
	Sampler samplerT34("\"sputnik\"", this, &selectableWorld, &inputManager,mOut, 44);
	samplerT34.setPosition(vec3(223.5f, 32.0f, -23.0f));
	samplerT34.setRotation(angleAxis(-90.0f, 0.0f ,1.0f, 0.0f));
	
	Player playerT3("break!", this, &selectableWorld, &inputManager, mOut, 46);
	playerT3.setPosition(vec3(180, 1, -40));
	playerT3.setRotation(angleAxis(-30.0f, 1.0f, 0.0f, 0.0f));
	
	
	
	// -- weight test --------------------------------------
	WeightTest wt1("1.0", props, vec3(0, 0, 40), 1.0f, &selectableWorld);
	WeightTest wt2("0.5", props, vec3(-10, 0, 40), 0.5f, &selectableWorld);
	WeightTest wt3("2.0", props, vec3(-20, 0, 40), 2.0f, &selectableWorld);
	WeightTest wt4("1.5", props, vec3(-30, 0, 40), 1.5f, &selectableWorld);
	
	
	
	// -- props -----------------------------
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
		// -- tier 1 ---------------
		sampler.update(deltaT, t);
		sampler2.update(deltaT, t);
		sampler3.update(deltaT, t);
		sampler4.update(deltaT, t);
		
		player.update(deltaT, t);
		tapeMachine.update(deltaT, t);
		
		// -- tier 2 ---------------
		samplerT21.update(deltaT, t);
		samplerT22.update(deltaT, t);
		samplerT23.update(deltaT, t);
		samplerT24.update(deltaT, t);
		
		playerT2.update(deltaT, t);

		// -- tier 3 ---------------
		samplerT31.update(deltaT, t);
		samplerT32.update(deltaT, t);
		samplerT33.update(deltaT, t);
		samplerT34.update(deltaT, t);
		
		playerT3.update(deltaT, t);
		
//		for (unsigned int i = 0; i < wpCount; i++)
//		{
//			section1[i]->update(deltaT, t);
//			section2[i]->update(deltaT, t);
//		}
		
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

			// -- tier 1 -------------
			sampler.render(RP_NORMAL, camera);
			sampler2.render(RP_NORMAL, camera);
			sampler3.render(RP_NORMAL, camera);
			sampler4.render(RP_NORMAL, camera);
			
			player.render(RP_NORMAL, camera);
			tapeMachine.render(RP_NORMAL, camera);

			// -- tier 2 -------------
			samplerT21.render(RP_NORMAL, camera);
			samplerT22.render(RP_NORMAL, camera);
			samplerT23.render(RP_NORMAL, camera);
			samplerT24.render(RP_NORMAL, camera);
			
			playerT2.render(RP_NORMAL, camera);

			// -- tier 3 -------------
			samplerT31.render(RP_NORMAL, camera);
			samplerT32.render(RP_NORMAL, camera);
			samplerT33.render(RP_NORMAL, camera);
			samplerT34.render(RP_NORMAL, camera);
			
			playerT3.render(RP_NORMAL, camera);
			
			
			for (unsigned int i = 0; i < wpCount; i++)
			{
				section1[i]->render(RP_NORMAL, camera);
				section2[i]->render(RP_NORMAL, camera);
			}
			
			
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
