#add_library(path_tracer_lib STATIC
#	Scene.cpp
#	
#)

#add_library("${PROJECT_NAME}" "")

#add_library(Func::Func ALIAS "${PROJECT_NAME}")

#target_include_directories("${PROJECT_NAME}" PUBLIC
#	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
#	"$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
#	"$<INSTALL_INTERFACE:include>" #${CMAKE_INSTALL_PREFIX}/include	
#)

add_executable(path_tracer
	main.cpp
	PathTracer.cpp
	PathTracer.h
	Scene.cpp
	Scene.h
	Ball.cpp
	Ball.h
	Camera.cpp
	Camera.h
	Image.cpp
	Image.h
	Material.cpp
	Material.h
	Metal.cpp
	Metal.h
	Ray.cpp
	Ray.h
	Sphere.cpp
	Sphere.h
	Color.cpp
	Color.h
	Dielectric.cpp
	Dielectric.h
)
target_link_libraries(
  path_tracer
  PRIVATE 
		#path_tracer_lib
		project_options
        #project_warnings)
		)