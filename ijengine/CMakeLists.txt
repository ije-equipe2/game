set(BASE_DIR "${PROJECT_SOURCE_DIR}/ijengine")

set (ENGINE_INCLUDE_DIR "${BASE_DIR}/include" CACHE INTERNAL "")
set (PROJECT_SRC_ENGINE_DIR     "${BASE_DIR}/src")
set (CMAKE_INCLUDE_OUTPUT_DIRECTORY "/usr/local/include/ijengine")

# Gets the list of files inside the src directory
file(GLOB_RECURSE SOURCES_IJENGINE "${PROJECT_SRC_ENGINE_DIR}/*.cpp")

include_directories("${ENGINE_INCLUDE_DIR}")

add_library(ijengine STATIC ${SOURCES_IJENGINE})

add_custom_command(TARGET ijengine POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${ENGINE_INCLUDE_DIR} ${CMAKE_INCLUDE_OUTPUT_DIRECTORY})