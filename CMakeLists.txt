cmake_minimum_required(VERSION 3.10)
project(SandboxEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL3 REQUIRED)

add_executable(
		${PROJECT_NAME} 
		main.cpp 
		sandbox.cpp
		renderer.cpp 
		board_renderer.cpp
		ui_renderer.cpp
		elements_data.cpp
		particles_manager.cpp
		particle_mover.cpp
		particle_dirs.cpp
		input_handler.cpp
		drawing_utility.cpp
		ui_anchor_modes.cpp
		ui_element.cpp
		ui_rect.cpp
		ui_label.cpp
		)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)


