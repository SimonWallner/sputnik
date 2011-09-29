# cmake list for src/

# -- git revision number magic -----------------------------------------------
# configure header file and append it to the other header files
configure_file("${PROJECT_SOURCE_DIR}/src/version.hpp.in" "${PROJECT_BINARY_DIR}/src/version.hpp")
list(APPEND INCLUDE_C_HEADER_FILES "${PROJECT_BINARY_DIR}/include/kocmoc-core/version.hpp")




# -- find stuff --------------------------------------------------------------
find_package(Boost COMPONENTS program_options)
if(NOT Boost_FOUND)
	message(WARNING "Boost not found!")
endif()

include_directories(
    ${PROJECT_SOURCE_DIR}/external/kocmoc-core/include
    ${PROJECT_BINARY_DIR}/external/kocmoc-core/include
	${PROJECT_BINARY_DIR}/src/
	${Boost_INCLUDE_DIR}
	${PROJECT_SOURCE_DIR}/external/kocmoc-core/external/glfw/include
	${PROJECT_SOURCE_DIR}/external/kocmoc-core/external/glm/include
)

link_directories(
	${Boost_LIBRARY_DIRS}
)

# collect the files
file(GLOB_RECURSE HEADER_FILES *.hpp)
file(GLOB_RECURSE SOURCE_FILES *.cpp)


add_executable(kocmoc ${SOURCE_FILES} ${HEADER_FILES})

set (TARGET_LINK_LIBRARIES kocmoc
    kocmoc-core
	${Boost_PROGRAM_OPTIONS_LIBRARY}
)

target_link_libraries(${TARGET_LINK_LIBRARIES})





