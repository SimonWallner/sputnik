#ifndef SPUTNIK_COMPONENT_CAMERA_DIST_TO_MIDI_HPP
#define SPUTNIK_COMPONENT_CAMERA_DIST_TO_MIDI_HPP

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/scene/FilmCamera.hpp>

namespace sputnik
{
	namespace component
	{
		class CameraDistToMidi : public kocmoc::core::componentSystem::Component
		{
		public:
			CameraDistToMidi(kocmoc::core::scene::FilmCamera* _camera,
							 output::MIDIOut* _mOut,
							 unsigned int _cc)
				: camera(_camera)
				, mOut(_mOut)
				, cc(_cc)
			{}
			
			void onUpdate(float deltaT, float t)
			{
				float dist = glm::length(camera->getPosition() - ob->position) / 100.0f;
				mOut->sendCC(cc, dist);

				UNUSED deltaT;
				UNUSED t;
			}
			
			void init()
			{
				ob = parent->getComponent<kocmoc::core::component::ObjectBehaviour>();
			}
			
		private:
			kocmoc::core::scene::FilmCamera* camera;
			kocmoc::core::component::ObjectBehaviour* ob;
			output::MIDIOut* mOut;
			unsigned int cc;
		};
	}
}

#endif
