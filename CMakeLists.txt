cmake_minimum_required(VERSION 3.0.2)
project(Deadly_Wish)


# Set directory folders
set (PROJECT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set (PROJECT_SRC_DIR     "${PROJECT_SOURCE_DIR}/src")
set (PROJECT_ASSETS_DIR  "${PROJECT_SOURCE_DIR}/res")
set (INSTALL_DIR "/usr/local")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${INSTALL_DIR}/lib")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${INSTALL_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DIR}/bin")
set (CMAKE_ASSETS_OUTPUT_DIRECTORY "${INSTALL_DIR}/share/deadlywish")

# Gets the list of files inside the src directory
file(GLOB_RECURSE SOURCES "${PROJECT_SRC_DIR}/*.cpp")

# Include Headers
include_directories("${PROJECT_INCLUDE_DIR}")



#### Compilation ####

# Compilation Flags
set(COMPILE_FLAGS "${COMPILE_FLAGS} -pedantic -std=c++11 -w -MMD -g3 -g -fPIC\
		 -W -Wall -Wextra -Wshadow -Wcast-align -Wcast-qual -Wctor-dtor-privacy\
		 -Wdisabled-optimization -Wformat=2 -Wlogical-op -Wmissing-declarations\
		 -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls\
		 -Wsign-promo -Wstrict-null-sentinel -Wswitch-default -Wundef\
		 -Wzero-as-null-pointer-constant -Wuseless-cast -Wnon-virtual-dtor")


set(kernel "-shared 
		 -rdynamic -std=c++11 -W -Wall -Wextra -Wshadow -Wcast-align -Wcast-qual -Wctor-dtor-privacy
		 -Wdisabled-optimization -Wformat=2 -Wlogical-op -Wmissing-declarations
		 -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls
		 -Wsign-promo -Wstrict-null-sentinel -Wswitch-default -Wundef
		 -Wzero-as-null-pointer-constant -Wuseless-cast -Wnon-virtual-dtor
		 -fPIC")

# Cmake compilation flags redefinition
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")


#### Dependencies ####


# Static Library
set (PROJECT_ENGINE_DIR "${PROJECT_SOURCE_DIR}/ijengine")
add_subdirectory(${PROJECT_ENGINE_DIR})
include_directories(${ENGINE_INCLUDE_DIR})

# Shared Library
set (PROJECT_SDL2_DIR "${PROJECT_SOURCE_DIR}/ijengine/kernel/sdl2")
add_subdirectory(${PROJECT_SDL2_DIR})
include_directories(${SDL2_INCLUDE_DIR})

#### Executable ####

add_executable(deadlywish ${SOURCES})

target_link_libraries(deadlywish
				  	  ijengine
                      SDL2 SDL2_image SDL2_ttf SDL2_mixer dl
					  kernel)



#### Custom Commands ####

# Copy assets folder to build
add_custom_command(TARGET deadlywish POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${PROJECT_ASSETS_DIR} ${CMAKE_ASSETS_OUTPUT_DIRECTORY})