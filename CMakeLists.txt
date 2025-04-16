cmake_minimum_required(VERSION 3.10)
project(SandboxEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL3 REQUIRED)

add_executable(
		${PROJECT_NAME} 
		main.cpp 
		renderer.cpp 
		particles_manager.cpp
		particle_mover.cpp
		input_handler.cpp
		drawing_utility.cpp
		)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)


