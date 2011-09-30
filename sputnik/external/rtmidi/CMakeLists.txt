# CMakelists file for the rtmidi lib

cmake_minimum_required(VERSION 2.8)
project(kocmoc-core CXX)

# ----------------- find stuff -------------------------
# find cocoa framework
find_library(CORE_MIDI_FRAMEWORK CoreMidi)
find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
find_library(CORE_AUDIO_FRAMEWORK CoreAudio)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(rtmidi
	src/RtMidi.cpp
	include/RtMidi.h
	include/RtError.h
)

target_link_libraries(rtmidi
	${CORE_MIDI_FRAMEWORK}
	${CORE_FOUNDATION_FRAMEWORK}
	${CORE_AUDIO_FRAMEWORK}
)