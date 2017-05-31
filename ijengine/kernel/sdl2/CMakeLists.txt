set(BASE_DIR "${PROJECT_SOURCE_DIR}/ijengine/kernel/sdl2")

set (SDL2_INCLUDE_DIR "${BASE_DIR}/ijengine/include" CACHE INTERNAL "")
set (PROJECT_SRC_LDL2_DIR     "${BASE_DIR}")

set (CMAKE_SHARED_LINKER_FLAGS "-shared -rdynamic")


# Gets the list of files inside the src directory
file(GLOB_RECURSE SOURCES_SDL2 "${PROJECT_SRC_LDL2_DIR}/*.cpp")

include_directories("${SDL2_INCLUDE_DIR}")

add_library(kernel SHARED ${SOURCES_SDL2})

set_target_properties(kernel PROPERTIES PREFIX ""
										SUFFIX ".so.0.1.0")

target_link_libraries(kernel ijengine)