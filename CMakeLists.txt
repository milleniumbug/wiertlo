cmake_minimum_required(VERSION 3.3)
project(wiertlo)

file(GLOB EXAMPLE_FILES "examples/*.cpp")
foreach(example ${EXAMPLE_FILES})
	get_filename_component(example_we ${example} NAME_WE)
	add_executable(${example_we} ${example})
	set_property(TARGET ${example_we} PROPERTY CXX_STANDARD 11)
	target_include_directories(${example_we}
	PUBLIC
		include
	PRIVATE
		examples)
endforeach()

set_property(TARGET map_ops PROPERTY CXX_STANDARD 14)
set_property(TARGET one_based_array_example PROPERTY CXX_STANDARD 14)
set_property(TARGET overload_set_example PROPERTY CXX_STANDARD 14)
set_property(TARGET tuple_example PROPERTY CXX_STANDARD 14)
set_property(TARGET interval_example PROPERTY CXX_STANDARD 14)
set_property(TARGET make_example PROPERTY CXX_STANDARD 14)
set_property(TARGET pimpl_handle_example PROPERTY CXX_STANDARD 14)