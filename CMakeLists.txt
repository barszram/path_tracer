cmake_minimum_required(VERSION 3.15)

project(path-tracer CXX)


add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(project_options INTERFACE -ftime-trace)
  endif()
endif()


option(ENABLE_TESTING "Enable Testing" OFF)
if(ENABLE_TESTING)
  enable_testing()
  message("Building Tests. Be sure to check out test/constexpr_tests for constexpr testing")
  add_subdirectory(test)
endif()


add_subdirectory(path_tracer)

if(NOT DEFINED ENV{VCPKG_ROOT})
    set(VCPKG_ROOT "G:/repository/vcpkg")
	include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
    set(VCPKG_TARGET_TRIPLET x64-windows)
endif()

find_package( glm CONFIG REQUIRED )
target_link_libraries( path_tracer PRIVATE glm::glm )
