# root build file for sputnik

cmake_minimum_required(VERSION 2.8)
project(sputnik CXX)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# xcode Product Name
set(APP_NAME sputnik)

# -- get it revision number (SHA1) -------------------------------------------
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC SPUTNIK_GIT_SHA1)
message(STATUS "SPUTNIK revision hash is: ${SPUTNIK_GIT_SHA1}")


# -- doxygen -----------------------------------------------------------------
set(KOCMOC_CORE_DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/docs)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${PROJECT_SOURCE_DIR}/Doxyfile.in ${PROJECT_BINARY_DIR}/Doxyfile)
add_custom_target(doc-sputnik
	${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
	COMMENT "Generating API documentation with Doxygen" VERBATIM
	)
endif(DOXYGEN_FOUND)

# -- check xml files ---------------------------------------------------------
set (XML_FILES 
	media/sputnik-config.xml.in
	)

foreach(f ${XML_FILES})
	execute_process(
		COMMAND xmllint ${f} --valid
		WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
		RESULT_VARIABLE XML_VALIDATION_RESULT
		OUTPUT_QUIET
		)

	if (XML_VALIDATION_RESULT) # 1 => error, 0 => OK
		message(WARNING "faild to validate xml file: ${f}")
	endif()
endforeach()


# -- copy and configure ------------------------------------------------------
message(STATUS "configuring files...")
set(KOCMOC_MEDIA_PATH ${PROJECT_SOURCE_DIR}/media/)
configure_file(media/sputnik-config.xml.in ${EXECUTABLE_OUTPUT_PATH}/sputnik-config.xml)

# set up parent media path, to allow the core to copy its config file
set(KOCMOC_CORE_CONFIG_TARGET_LOCATION ${EXECUTABLE_OUTPUT_PATH}/kocmoc-core-config.xml)

# -- add subdirs -------------------------------------------------------------
add_subdirectory(external/kocmoc-core)
add_subdirectory(external/rtmidi)
add_subdirectory(src)
